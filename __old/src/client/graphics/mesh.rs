use crate::*;
use wgpu::util::DeviceExt;

#[derive(Debug, Clone, PartialEq, PartialOrd, derive_builder::Builder)]
#[builder(setter(into))]
pub struct MeshConfig {
    #[builder(default = "\"Vertex Buffer\".into()")]
    pub vertex_buffer_label: String,
    #[builder(default)]
    pub vertex_buffer_contents: Vec<client::graphics::vertex::Vertex>,
    #[builder(default = "wgpu::BufferUsage::VERTEX")]
    pub vertex_buffer_usage: wgpu::BufferUsage,
    #[builder(default = "\"Index Buffer\".into()")]
    pub index_buffer_label: String,
    #[builder(default)]
    pub index_buffer_contents: Vec<client::graphics::index::Index>,
    #[builder(default = "wgpu::BufferUsage::INDEX")]
    pub index_buffer_usage: wgpu::BufferUsage,
}

#[derive(Debug)]
pub struct Mesh {
    pub config: MeshConfig,
    pub vertex_buffer: wgpu::Buffer,
    pub index_buffer: wgpu::Buffer,
}

impl Mesh {
    pub fn new(config: MeshConfig, renderer: &client::graphics::renderer::Renderer) -> Self {
        let vertex_buffer = renderer
            .device
            .create_buffer_init(&wgpu::util::BufferInitDescriptor {
                label: Some(&config.vertex_buffer_label),
                contents: bytemuck::cast_slice(&config.vertex_buffer_contents),
                usage: config.vertex_buffer_usage,
            });
        let index_buffer = renderer
            .device
            .create_buffer_init(&wgpu::util::BufferInitDescriptor {
                label: Some(&config.index_buffer_label),
                contents: bytemuck::cast_slice(&config.index_buffer_contents),
                usage: config.index_buffer_usage,
            });

        Self {
            config,
            vertex_buffer,
            index_buffer,
        }
    }
}
