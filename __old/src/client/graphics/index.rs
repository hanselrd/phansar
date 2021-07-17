type IndexType = u16;

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
    derive_more::Constructor,
    derive_more::From,
)]
pub struct Index(pub IndexType);

impl Index {
    pub fn format() -> wgpu::IndexFormat {
        if std::any::TypeId::of::<IndexType>() == std::any::TypeId::of::<u16>() {
            wgpu::IndexFormat::Uint16
        } else {
            assert!(std::any::TypeId::of::<IndexType>() == std::any::TypeId::of::<u32>());

            wgpu::IndexFormat::Uint32
        }
    }
}
