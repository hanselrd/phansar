fn main() {
    println!(
        "Hello, world! {} {}",
        String::from_utf8_lossy(phansar_assets::ASSETS_SHADERS_SHADER_WGSL),
        phansar_assets::ASSETS_SHADERS_SHADER_WGSL.len()
    );
}
