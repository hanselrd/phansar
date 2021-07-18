fn main() {
    let app = phansar_common::Application::new(
        phansar_common::ApplicationConfigBuilder::default()
            .name("Phansar Client")
            .about("Phansar Client")
            .build()
            .unwrap(),
    );

    app.runtime.block_on(async {
        log::trace!("test");
        log::debug!("test");
        log::info!("test");
        log::warn!("test");
        log::error!("test");
        // println!(
        //     "Hello, world! {} {}",
        //     String::from_utf8_lossy(phansar_assets::ASSETS_SHADERS_SHADER_WGSL),
        //     phansar_assets::ASSETS_SHADERS_SHADER_WGSL.len()
        // );
    });
}
