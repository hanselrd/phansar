#[repr(C)]
#[derive(
    Debug,
    Default,
    Copy,
    Clone,
    PartialEq,
    PartialOrd,
    serde::Serialize,
    serde::Deserialize,
    bytemuck::Pod,
    bytemuck::Zeroable,
    derive_builder::Builder,
)]
#[builder(setter(into))]
pub struct Vertex {
    pub position: [f32; 3],
    #[builder(default = "[0.0, 0.0, 0.0]")]
    pub normal: [f32; 3],
    #[builder(default = "[0.0, 0.0, 0.0]")]
    pub tangent: [f32; 3],
    #[builder(default = "[0.0, 0.0, 0.0]")]
    pub bitangent: [f32; 3],
    #[builder(default = "[1.0, 1.0, 1.0, 1.0]")]
    pub color: [f32; 4],
    #[builder(default = "[0.0, 0.0]")]
    pub tex_coords: [f32; 2],
}

impl<'a> Vertex {
    const ATTRIBUTES: &'a [wgpu::VertexAttribute] = &wgpu::vertex_attr_array![
        0 => Float32x3,
        1 => Float32x3,
        2 => Float32x3,
        3 => Float32x3,
        4 => Float32x4,
        5 => Float32x2,
    ];

    pub fn layout() -> wgpu::VertexBufferLayout<'a> {
        wgpu::VertexBufferLayout {
            array_stride: std::mem::size_of::<Vertex>() as wgpu::BufferAddress,
            step_mode: wgpu::InputStepMode::Vertex,
            attributes: Self::ATTRIBUTES,
        }
    }
}
