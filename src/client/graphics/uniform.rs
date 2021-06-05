use cgmath::SquareMatrix;

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
pub struct Uniform {
    #[builder(default = "cgmath::Matrix4::identity().into()")]
    pub view_proj: [[f32; 4]; 4],
}
