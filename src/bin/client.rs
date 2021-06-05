use cgmath::{InnerSpace, Rotation3, Zero};
use phansar::*;
use wgpu::util::DeviceExt;

const NUM_INSTANCES_PER_ROW: u32 = 10;
const INSTANCE_DISPLACEMENT: cgmath::Vector3<f32> = cgmath::Vector3::new(
    NUM_INSTANCES_PER_ROW as f32 * 0.5,
    0.0,
    NUM_INSTANCES_PER_ROW as f32 * 0.5,
);

lazy_static::lazy_static! {
    static ref VERTICES: Vec<client::graphics::vertex::Vertex> = vec![
        client::graphics::vertex::VertexBuilder::default()
            .position([-0.0868241, 0.49240386, 0.0])
            .color([0.5, 0.0, 0.5, 1.0])
            .tex_coords([0.4131759, 0.99240386])
            .build()
            .unwrap(), // A
        client::graphics::vertex::VertexBuilder::default()
            .position([-0.49513406, 0.06958647, 0.0])
            .color([0.5, 0.0, 0.5, 1.0])
            .tex_coords([0.0048659444, 0.56958646])
            .build()
            .unwrap(), // B
        client::graphics::vertex::VertexBuilder::default()
            .position([-0.21918549, -0.44939706, 0.0])
            .color([0.5, 0.0, 0.5, 1.0])
            .tex_coords([0.28081453, 0.050602943])
            .build()
            .unwrap(), // C
        client::graphics::vertex::VertexBuilder::default()
            .position([0.35966998, -0.3473291, 0.0])
            .color([0.5, 0.0, 0.5, 1.0])
            .tex_coords([0.85967, 0.15267089])
            .build()
            .unwrap(), // D
        client::graphics::vertex::VertexBuilder::default()
            .position([0.44147372, 0.2347359, 0.0])
            .color([0.5, 0.0, 0.5, 1.0])
            .tex_coords([0.9414737, 0.7347359])
            .build()
            .unwrap(), // E
    ];
}

const INDICES: &[client::graphics::index::Index] = &[
    client::graphics::index::Index(0),
    client::graphics::index::Index(1),
    client::graphics::index::Index(4),
    client::graphics::index::Index(1),
    client::graphics::index::Index(2),
    client::graphics::index::Index(4),
    client::graphics::index::Index(2),
    client::graphics::index::Index(3),
    client::graphics::index::Index(4),
];

struct State {
    renderer: client::graphics::renderer::Renderer,
    render_pipeline: wgpu::RenderPipeline,
    vertex_buffer: wgpu::Buffer,
    index_buffer: wgpu::Buffer,
    depth_texture: client::graphics::texture::Texture,
    #[allow(dead_code)]
    diffuse_texture: client::graphics::texture::Texture,
    diffuse_bind_group: wgpu::BindGroup,
    #[allow(dead_code)]
    camera: client::graphics::camera::Camera,
    #[allow(dead_code)]
    uniform: client::graphics::uniform::Uniform,
    #[allow(dead_code)]
    uniform_buffer: wgpu::Buffer,
    uniform_bind_group: wgpu::BindGroup,
    instances: Vec<client::graphics::instance::Instance>,
    instance_buffer: wgpu::Buffer,
}

impl State {
    fn new(window: &winit::window::Window) -> Self {
        let renderer = client::graphics::renderer::Renderer::new(
            client::graphics::renderer::RendererConfigBuilder::default()
                .build()
                .unwrap(),
            window,
        );
        let texture_bind_group_layout =
            renderer
                .device
                .create_bind_group_layout(&wgpu::BindGroupLayoutDescriptor {
                    label: Some("texture_bind_group_layout"),
                    entries: &[
                        wgpu::BindGroupLayoutEntry {
                            binding: 0,
                            visibility: wgpu::ShaderStage::FRAGMENT,
                            ty: wgpu::BindingType::Texture {
                                multisampled: false,
                                view_dimension: wgpu::TextureViewDimension::D2,
                                sample_type: wgpu::TextureSampleType::Float { filterable: true },
                            },
                            count: None,
                        },
                        wgpu::BindGroupLayoutEntry {
                            binding: 1,
                            visibility: wgpu::ShaderStage::FRAGMENT,
                            ty: wgpu::BindingType::Sampler {
                                comparison: false,
                                filtering: true,
                            },
                            count: None,
                        },
                    ],
                });
        let depth_texture =
            client::graphics::texture::Texture::create_depth_texture(&renderer, "depth");
        let diffuse_bytes =
            include_bytes!(concat!(env!("OUT_DIR"), "/assets/textures/container.png"));
        let diffuse_texture =
            client::graphics::texture::Texture::from_bytes(&renderer, diffuse_bytes, "container");
        let diffuse_bind_group = renderer
            .device
            .create_bind_group(&wgpu::BindGroupDescriptor {
                label: Some("diffuse_bind_group"),
                layout: &texture_bind_group_layout,
                entries: &[
                    wgpu::BindGroupEntry {
                        binding: 0,
                        resource: wgpu::BindingResource::TextureView(&diffuse_texture.view),
                    },
                    wgpu::BindGroupEntry {
                        binding: 1,
                        resource: wgpu::BindingResource::Sampler(&diffuse_texture.sampler),
                    },
                ],
            });
        let camera = client::graphics::camera::CameraBuilder::default()
            .eye((0.0, 2.0, 10.0))
            .center((0.0, 0.0, -100.0))
            .aspect(
                renderer.swap_chain_descriptor.width as f32
                    / renderer.swap_chain_descriptor.height as f32,
            )
            .build()
            .unwrap();
        log::info!("CAMERA: {:#?}", camera);
        let uniform = client::graphics::uniform::UniformBuilder::default()
            .view_proj(camera.view_projection_matrix())
            .build()
            .unwrap();
        let uniform_buffer =
            renderer
                .device
                .create_buffer_init(&wgpu::util::BufferInitDescriptor {
                    label: Some("Uniform Buffer"),
                    contents: bytemuck::cast_slice(&[uniform]),
                    usage: wgpu::BufferUsage::UNIFORM | wgpu::BufferUsage::COPY_DST,
                });
        let uniform_bind_group_layout =
            renderer
                .device
                .create_bind_group_layout(&wgpu::BindGroupLayoutDescriptor {
                    label: Some("uniform_bind_group_layout"),
                    entries: &[wgpu::BindGroupLayoutEntry {
                        binding: 0,
                        visibility: wgpu::ShaderStage::VERTEX,
                        ty: wgpu::BindingType::Buffer {
                            ty: wgpu::BufferBindingType::Uniform,
                            has_dynamic_offset: false,
                            min_binding_size: None,
                        },
                        count: None,
                    }],
                });
        let uniform_bind_group = renderer
            .device
            .create_bind_group(&wgpu::BindGroupDescriptor {
                label: Some("uniform_bind_group"),
                layout: &uniform_bind_group_layout,
                entries: &[wgpu::BindGroupEntry {
                    binding: 0,
                    resource: uniform_buffer.as_entire_binding(),
                }],
            });
        let instances = (0..NUM_INSTANCES_PER_ROW)
            .flat_map(|z| {
                (0..NUM_INSTANCES_PER_ROW).map(move |x| {
                    let translation = cgmath::Vector3 {
                        x: x as f32,
                        y: 0.0,
                        z: z as f32,
                    } - INSTANCE_DISPLACEMENT;
                    let rotation = if translation.is_zero() {
                        cgmath::Quaternion::from_axis_angle(
                            cgmath::Vector3::unit_z(),
                            cgmath::Deg(0.0),
                        )
                    } else {
                        cgmath::Quaternion::from_axis_angle(
                            translation.normalize(),
                            cgmath::Deg(45.0),
                        )
                    };
                    let scale = cgmath::Vector3::new(0.7, 0.7, 0.7);

                    client::graphics::instance::InstanceBuilder::default()
                        .model_srt(scale, rotation, translation)
                        .build()
                        .unwrap()
                })
            })
            .collect::<Vec<_>>();
        let instance_buffer =
            renderer
                .device
                .create_buffer_init(&wgpu::util::BufferInitDescriptor {
                    label: Some("Instance Buffer"),
                    contents: bytemuck::cast_slice(&instances),
                    usage: wgpu::BufferUsage::VERTEX | wgpu::BufferUsage::COPY_DST,
                });
        let shader_module = renderer
            .device
            .create_shader_module(&wgpu::ShaderModuleDescriptor {
                label: Some("Shader"),
                flags: wgpu::ShaderFlags::all(),
                source: wgpu::ShaderSource::Wgsl(
                    include_str!(concat!(env!("OUT_DIR"), "/assets/shaders/shader.wgsl")).into(),
                ),
            });
        let pipeline_layout =
            renderer
                .device
                .create_pipeline_layout(&wgpu::PipelineLayoutDescriptor {
                    label: Some("Render Pipeline Layout"),
                    bind_group_layouts: &[&uniform_bind_group_layout, &texture_bind_group_layout],
                    push_constant_ranges: &[],
                });
        let render_pipeline =
            renderer
                .device
                .create_render_pipeline(&wgpu::RenderPipelineDescriptor {
                    label: Some("Render Pipeline"),
                    layout: Some(&pipeline_layout),
                    vertex: wgpu::VertexState {
                        module: &shader_module,
                        entry_point: "main",
                        buffers: &[
                            client::graphics::vertex::Vertex::layout(),
                            client::graphics::instance::Instance::layout(),
                        ],
                    },
                    fragment: Some(wgpu::FragmentState {
                        module: &shader_module,
                        entry_point: "main",
                        targets: &[wgpu::ColorTargetState {
                            format: renderer.swap_chain_descriptor.format,
                            blend: Some(wgpu::BlendState::REPLACE),
                            write_mask: wgpu::ColorWrite::ALL,
                        }],
                    }),
                    primitive: wgpu::PrimitiveState {
                        topology: wgpu::PrimitiveTopology::TriangleList,
                        strip_index_format: None,
                        front_face: wgpu::FrontFace::Ccw,
                        cull_mode: Some(wgpu::Face::Back),
                        polygon_mode: wgpu::PolygonMode::Fill,
                        clamp_depth: false,
                        conservative: false,
                    },
                    depth_stencil: Some(wgpu::DepthStencilState {
                        format: wgpu::TextureFormat::Depth32Float,
                        depth_write_enabled: true,
                        depth_compare: wgpu::CompareFunction::Less,
                        stencil: wgpu::StencilState::default(),
                        bias: wgpu::DepthBiasState::default(),
                    }),
                    multisample: wgpu::MultisampleState {
                        count: 1,
                        mask: !0,
                        alpha_to_coverage_enabled: false,
                    },
                });
        let vertex_buffer = renderer
            .device
            .create_buffer_init(&wgpu::util::BufferInitDescriptor {
                label: Some("Vertex Buffer"),
                contents: bytemuck::cast_slice(&*VERTICES),
                usage: wgpu::BufferUsage::VERTEX,
            });
        let index_buffer = renderer
            .device
            .create_buffer_init(&wgpu::util::BufferInitDescriptor {
                label: Some("Index Buffer"),
                contents: bytemuck::cast_slice(INDICES),
                usage: wgpu::BufferUsage::INDEX,
            });

        Self {
            renderer,
            render_pipeline,
            vertex_buffer,
            index_buffer,
            depth_texture,
            diffuse_texture,
            diffuse_bind_group,
            camera,
            uniform,
            uniform_buffer,
            uniform_bind_group,
            instances,
            instance_buffer,
        }
    }

    fn resize(&mut self, new_size: winit::dpi::PhysicalSize<u32>) {
        self.renderer.swap_chain_descriptor.width = new_size.width;
        self.renderer.swap_chain_descriptor.height = new_size.height;
        self.renderer.swap_chain = self
            .renderer
            .device
            .create_swap_chain(&self.renderer.surface, &self.renderer.swap_chain_descriptor);
        self.depth_texture =
            client::graphics::texture::Texture::create_depth_texture(&self.renderer, "depth");
    }

    #[allow(unused_variables)]
    fn input(&mut self, event: &winit::event::WindowEvent) -> bool {
        // match event {
        //     | winit::event::WindowEvent::CursorMoved { position, .. } => {
        //         self.clear_color = wgpu::Color {
        //             r: position.x / self.size.width as f64,
        //             g: position.y / self.size.height as f64,
        //             b: 1.0,
        //             a: 1.0,
        //         };
        //         true
        //     }
        //     | _ => false,
        // }
        false
    }

    fn update(&mut self) {
        self.uniform.view_proj = self.camera.view_projection_matrix().into();
        self.renderer.queue.write_buffer(
            &self.uniform_buffer,
            0,
            bytemuck::cast_slice(&[self.uniform]),
        );
        self.renderer.queue.write_buffer(
            &self.instance_buffer,
            0,
            bytemuck::cast_slice(&self.instances),
        );
    }

    fn render(&mut self) -> Result<(), wgpu::SwapChainError> {
        let frame = self.renderer.swap_chain.get_current_frame()?.output;
        let mut encoder =
            self.renderer
                .device
                .create_command_encoder(&wgpu::CommandEncoderDescriptor {
                    label: Some("Render Encoder"),
                });
        let mut render_pass = encoder.begin_render_pass(&wgpu::RenderPassDescriptor {
            label: Some("Render Pass"),
            color_attachments: &[wgpu::RenderPassColorAttachment {
                view: &frame.view,
                resolve_target: None,
                ops: wgpu::Operations {
                    load: wgpu::LoadOp::Clear(wgpu::Color::BLACK),
                    store: true,
                },
            }],
            depth_stencil_attachment: Some(wgpu::RenderPassDepthStencilAttachment {
                view: &self.depth_texture.view,
                depth_ops: Some(wgpu::Operations {
                    load: wgpu::LoadOp::Clear(1.0),
                    store: true,
                }),
                stencil_ops: None,
            }),
        });

        render_pass.set_pipeline(&self.render_pipeline);
        render_pass.set_bind_group(0, &self.uniform_bind_group, &[]);
        render_pass.set_bind_group(1, &self.diffuse_bind_group, &[]);
        render_pass.set_vertex_buffer(0, self.vertex_buffer.slice(..));
        render_pass.set_vertex_buffer(1, self.instance_buffer.slice(..));
        render_pass.set_index_buffer(
            self.index_buffer.slice(..),
            client::graphics::index::Index::format(),
        );
        render_pass.draw_indexed(0..INDICES.len() as _, 0, 0..self.instances.len() as _);
        drop(render_pass);

        self.renderer
            .queue
            .submit(std::iter::once(encoder.finish()));

        Ok(())
    }
}

fn main() {
    env_logger::Builder::from_env(env_logger::Env::default().default_filter_or(
        if cfg!(debug_assertions) {
            "trace"
        } else {
            "client=info,server=info,phansar=info"
        },
    ))
    .init();

    log::trace!("{}", common::version::VERSION_STRING);
    log::debug!("{}", common::version::VERSION_STRING);
    log::info!("{}", common::version::VERSION_STRING);
    log::warn!("{}", common::version::VERSION_STRING);
    log::error!("{}", common::version::VERSION_STRING);

    log::trace!("VERTICES(debug): {:#?}", *VERTICES);
    log::trace!("INDICES(debug): {:#?}", INDICES);
    log::trace!(
        "VERTICES(json): {}",
        serde_json::to_string(&*VERTICES).unwrap()
    );
    log::trace!(
        "INDICES(json): {}",
        serde_json::to_string(&INDICES).unwrap()
    );

    let event_loop = winit::event_loop::EventLoop::new();
    let window = winit::window::WindowBuilder::new()
        .build(&event_loop)
        .unwrap();
    let mut state = State::new(&window);

    event_loop.run(move |event, _, control_flow| match event {
        | winit::event::Event::WindowEvent {
            ref event,
            window_id,
        } if window_id == window.id() => {
            if !state.input(event) {
                match event {
                    | winit::event::WindowEvent::CloseRequested => {
                        *control_flow = winit::event_loop::ControlFlow::Exit
                    }
                    | winit::event::WindowEvent::KeyboardInput { input, .. } => match input {
                        | winit::event::KeyboardInput {
                            state: winit::event::ElementState::Pressed,
                            virtual_keycode: Some(winit::event::VirtualKeyCode::Escape),
                            ..
                        } => *control_flow = winit::event_loop::ControlFlow::Exit,
                        | _ => {}
                    },
                    | winit::event::WindowEvent::Resized(physical_size) => {
                        state.resize(*physical_size);
                    }
                    | winit::event::WindowEvent::ScaleFactorChanged { new_inner_size, .. } => {
                        state.resize(**new_inner_size);
                    }
                    | _ => {}
                }
            }
        }
        | winit::event::Event::RedrawRequested(_) => {
            state.update();
            match state.render() {
                | Ok(_) => {}
                | Err(wgpu::SwapChainError::Lost) => state.resize(state.renderer.size()),
                | Err(wgpu::SwapChainError::OutOfMemory) => {
                    *control_flow = winit::event_loop::ControlFlow::Exit
                }
                | Err(e) => log::error!("{:?}", e),
            }
        }
        | winit::event::Event::MainEventsCleared => {
            window.request_redraw();
        }
        | _ => {}
    });
}
