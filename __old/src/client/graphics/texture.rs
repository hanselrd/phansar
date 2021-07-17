use crate::*;
use image::GenericImageView;

#[derive(Debug, Clone, PartialEq, derive_builder::Builder)]
#[builder(setter(into))]
pub struct TextureConfig {
    #[builder(default = "\"Texture\".into()")]
    pub texture_label: String,
    #[builder(default = "wgpu::Extent3d { width: 1, height: 1, depth_or_array_layers: 1 }")]
    pub texture_size: wgpu::Extent3d,
    #[builder(default = "1")]
    pub texture_mip_level_count: u32,
    #[builder(default = "1")]
    pub texture_sample_count: u32,
    #[builder(default = "wgpu::TextureDimension::D2")]
    pub texture_dimension: wgpu::TextureDimension,
    #[builder(default = "wgpu::TextureFormat::Rgba8UnormSrgb")]
    pub texture_format: wgpu::TextureFormat,
    #[builder(default = "wgpu::TextureUsage::SAMPLED | wgpu::TextureUsage::COPY_DST")]
    pub texture_usage: wgpu::TextureUsage,
    #[builder(default = "\"Sampler\".into()")]
    pub sampler_label: String,
    #[builder(default = "wgpu::AddressMode::ClampToEdge")]
    pub sampler_address_mode_u: wgpu::AddressMode,
    #[builder(default = "wgpu::AddressMode::ClampToEdge")]
    pub sampler_address_mode_v: wgpu::AddressMode,
    #[builder(default = "wgpu::AddressMode::ClampToEdge")]
    pub sampler_address_mode_w: wgpu::AddressMode,
    #[builder(default = "wgpu::FilterMode::Linear")]
    pub sampler_mag_filter: wgpu::FilterMode,
    #[builder(default = "wgpu::FilterMode::Nearest")]
    pub sampler_min_filter: wgpu::FilterMode,
    #[builder(default = "wgpu::FilterMode::Nearest")]
    pub sampler_mipmap_filter: wgpu::FilterMode,
    #[builder(default = "0.0")]
    pub sampler_lod_min_clamp: f32,
    #[builder(default = "std::f32::MAX")]
    pub sampler_lod_max_clamp: f32,
    #[builder(default)]
    pub sampler_compare: Option<wgpu::CompareFunction>,
    #[builder(default)]
    pub sampler_anisotropy_clamp: Option<std::num::NonZeroU8>,
    #[builder(default)]
    pub sampler_border_color: Option<wgpu::SamplerBorderColor>,
}

#[derive(Debug)]
pub struct Texture {
    pub config: TextureConfig,
    pub texture: wgpu::Texture,
    pub view: wgpu::TextureView,
    pub sampler: wgpu::Sampler,
}

impl Texture {
    pub fn new(config: TextureConfig, renderer: &client::graphics::renderer::Renderer) -> Self {
        let texture = renderer.device.create_texture(&wgpu::TextureDescriptor {
            label: Some(&config.texture_label),
            size: config.texture_size,
            mip_level_count: config.texture_mip_level_count,
            sample_count: config.texture_sample_count,
            dimension: config.texture_dimension,
            format: config.texture_format,
            usage: config.texture_usage,
        });
        let view = texture.create_view(&wgpu::TextureViewDescriptor::default());
        let sampler = renderer.device.create_sampler(&wgpu::SamplerDescriptor {
            label: Some(&config.sampler_label),
            address_mode_u: config.sampler_address_mode_u,
            address_mode_v: config.sampler_address_mode_v,
            address_mode_w: config.sampler_address_mode_w,
            mag_filter: config.sampler_mag_filter,
            min_filter: config.sampler_min_filter,
            mipmap_filter: config.sampler_mipmap_filter,
            lod_min_clamp: config.sampler_lod_min_clamp,
            lod_max_clamp: config.sampler_lod_max_clamp,
            compare: config.sampler_compare,
            anisotropy_clamp: config.sampler_anisotropy_clamp,
            border_color: config.sampler_border_color,
        });

        Self {
            config,
            texture,
            view,
            sampler,
        }
    }

    pub fn create_depth_texture(renderer: &client::graphics::renderer::Renderer) -> Self {
        Self::new(
            TextureConfigBuilder::default()
                .texture_size(wgpu::Extent3d {
                    width: renderer.swap_chain_descriptor.width,
                    height: renderer.swap_chain_descriptor.height,
                    depth_or_array_layers: 1,
                })
                .texture_format(wgpu::TextureFormat::Depth32Float)
                .texture_usage(wgpu::TextureUsage::RENDER_ATTACHMENT | wgpu::TextureUsage::SAMPLED)
                .sampler_mag_filter(wgpu::FilterMode::Linear)
                .sampler_min_filter(wgpu::FilterMode::Linear)
                .sampler_mipmap_filter(wgpu::FilterMode::Nearest)
                .sampler_lod_min_clamp(-100.0)
                .sampler_lod_max_clamp(100.0)
                .sampler_compare(wgpu::CompareFunction::LessEqual)
                .build()
                .unwrap(),
            renderer,
        )
    }

    pub fn from_image(
        renderer: &client::graphics::renderer::Renderer,
        img: &image::DynamicImage,
    ) -> Self {
        let rgba = img.as_rgba8().unwrap();
        let dimensions = img.dimensions();
        let size = wgpu::Extent3d {
            width: dimensions.0,
            height: dimensions.1,
            depth_or_array_layers: 1,
        };
        let new = Self::new(
            TextureConfigBuilder::default()
                .texture_size(size)
                .build()
                .unwrap(),
            renderer,
        );

        renderer.queue.write_texture(
            wgpu::ImageCopyTexture {
                texture: &new.texture,
                mip_level: 0,
                origin: wgpu::Origin3d::ZERO,
            },
            rgba,
            wgpu::ImageDataLayout {
                offset: 0,
                bytes_per_row: std::num::NonZeroU32::new(4 * dimensions.0),
                rows_per_image: std::num::NonZeroU32::new(dimensions.1),
            },
            size,
        );

        new
    }

    pub fn from_bytes(renderer: &client::graphics::renderer::Renderer, bytes: &[u8]) -> Self {
        let img = image::load_from_memory(bytes).unwrap();

        Self::from_image(renderer, &img)
    }
}
