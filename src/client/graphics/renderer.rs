#[derive(Debug, derive_builder::Builder)]
#[builder(setter(into))]
pub struct RendererConfig {
    #[builder(default = "wgpu::BackendBit::PRIMARY")]
    pub instance_backends: wgpu::BackendBit,
    #[builder(default)]
    pub adapter_power_preference: wgpu::PowerPreference,
    #[builder(default = "\"Device\".into()")]
    pub device_label: String,
    #[builder(default = "wgpu::Features::empty()")]
    pub device_features: wgpu::Features,
    #[builder(default)]
    pub device_limits: wgpu::Limits,
}

#[derive(Debug)]
pub struct Renderer {
    pub config: RendererConfig,
    pub instance: wgpu::Instance,
    pub surface: wgpu::Surface,
    pub adapter: wgpu::Adapter,
    pub device: wgpu::Device,
    pub queue: wgpu::Queue,
    pub swap_chain_descriptor: wgpu::SwapChainDescriptor,
    pub swap_chain: wgpu::SwapChain,
}

impl Renderer {
    pub fn new(config: RendererConfig, window: &winit::window::Window) -> Self {
        let instance = wgpu::Instance::new(config.instance_backends);
        let surface = unsafe { instance.create_surface(window) };
        let adapter =
            futures::executor::block_on(instance.request_adapter(&wgpu::RequestAdapterOptions {
                power_preference: config.adapter_power_preference,
                compatible_surface: Some(&surface),
            }))
            .unwrap();
        let (device, queue) = futures::executor::block_on(adapter.request_device(
            &wgpu::DeviceDescriptor {
                label: Some(&config.device_label),
                features: config.device_features,
                limits: Clone::clone(&config.device_limits),
            },
            None,
        ))
        .unwrap();
        let swap_chain_descriptor = wgpu::SwapChainDescriptor {
            usage: wgpu::TextureUsage::RENDER_ATTACHMENT,
            format: adapter.get_swap_chain_preferred_format(&surface).unwrap(),
            width: window.inner_size().width,
            height: window.inner_size().height,
            present_mode: wgpu::PresentMode::Fifo,
        };
        let swap_chain = device.create_swap_chain(&surface, &swap_chain_descriptor);

        Self {
            config,
            instance,
            surface,
            adapter,
            device,
            queue,
            swap_chain_descriptor,
            swap_chain,
        }
    }

    pub fn size(&self) -> winit::dpi::PhysicalSize<u32> {
        let wgpu::SwapChainDescriptor { width, height, .. } = self.swap_chain_descriptor;

        winit::dpi::PhysicalSize::<u32>::new(width, height)
    }
}
