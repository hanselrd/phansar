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
pub struct Instance {
    #[builder(default = "cgmath::Matrix4::identity().into()")]
    pub model: [[f32; 4]; 4],
    #[builder(default = "cgmath::Matrix3::identity().into()")]
    pub normal: [[f32; 3]; 3],
}

impl<'a> Instance {
    const ATTRIBUTES: &'a [wgpu::VertexAttribute] = &wgpu::vertex_attr_array![
        6 => Float32x4,
        7 => Float32x4,
        8 => Float32x4,
        9 => Float32x4,
        10 => Float32x3,
        11 => Float32x3,
        12 => Float32x3,
    ];

    pub fn layout() -> wgpu::VertexBufferLayout<'a> {
        wgpu::VertexBufferLayout {
            array_stride: std::mem::size_of::<Instance>() as wgpu::BufferAddress,
            step_mode: wgpu::InputStepMode::Instance,
            attributes: Self::ATTRIBUTES,
        }
    }
}

impl InstanceBuilder {
    pub fn model_srt(
        &mut self,
        scale: cgmath::Vector3<f32>,
        rotation: cgmath::Quaternion<f32>,
        translation: cgmath::Vector3<f32>,
    ) -> &mut Self {
        let mut new = self;
        new.model = Some(
            (cgmath::Matrix4::from_translation(translation)
                * cgmath::Matrix4::from(rotation)
                * cgmath::Matrix4::from_nonuniform_scale(scale.x, scale.y, scale.z))
            .into(),
        );
        new.normal = Some(cgmath::Matrix3::from(rotation).into());

        new
    }
}
