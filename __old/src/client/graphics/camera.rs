#[derive(Debug, Copy, Clone, PartialEq, derive_builder::Builder)]
#[builder(setter(into))]
pub struct Camera {
    #[builder(default = "[0.0, 0.0, 1.0].into()")]
    pub eye: cgmath::Point3<f32>,
    #[builder(default = "[0.0, 0.0, 0.0].into()")]
    pub center: cgmath::Point3<f32>,
    #[builder(default = "cgmath::Vector3::unit_y()")]
    pub up: cgmath::Vector3<f32>,
    #[builder(default = "45.0")]
    pub fovy: f32,
    pub aspect: f32,
    #[builder(default = "0.1")]
    pub near: f32,
    #[builder(default = "100.0")]
    pub far: f32,
}

impl Camera {
    #[rustfmt::skip]
    const OPENGL_TO_WGPU_MATRIX: cgmath::Matrix4<f32> = cgmath::Matrix4::new(
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 0.5, 0.0,
        0.0, 0.0, 0.5, 1.0,
    );

    pub fn view_projection_matrix(&self) -> cgmath::Matrix4<f32> {
        let view = cgmath::Matrix4::look_at_rh(self.eye, self.center, self.up);
        let projection =
            cgmath::perspective(cgmath::Deg(self.fovy), self.aspect, self.near, self.far);

        Self::OPENGL_TO_WGPU_MATRIX * projection * view
    }
}
