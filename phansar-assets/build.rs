use convert_case::Casing;
use std::io::Write;

fn get_files_recursively<P>(path: P) -> Vec<std::path::PathBuf>
where
    P: AsRef<std::path::Path>,
{
    std::fs::read_dir(path)
        .unwrap()
        .map(|entry| entry.unwrap())
        .filter_map(|entry| {
            if let Ok(file_type) = entry.file_type() {
                if file_type.is_dir() {
                    return Some(get_files_recursively(entry.path()));
                } else if file_type.is_file() {
                    return Some(vec![entry.path()]);
                }
            }

            None
        })
        .flatten()
        .collect()
}

fn main() {
    let cargo_manifest_dir = std::env::var("CARGO_MANIFEST_DIR").unwrap();
    let out_dir = std::env::var("OUT_DIR").unwrap();

    let assets_path = std::path::PathBuf::from(&cargo_manifest_dir).join("assets");

    let output_path = std::path::PathBuf::from(&out_dir).join("codegen.rs");
    let mut output = std::fs::File::create(output_path).unwrap();

    let re = regex::Regex::new(r"[\W_]").unwrap();

    for asset in get_files_recursively(assets_path) {
        let name = asset
            .strip_prefix(&cargo_manifest_dir)
            .unwrap()
            .to_string_lossy()
            .to_string();
        let name = re
            .replace_all(&name, "_")
            .to_case(convert_case::Case::ScreamingSnake);

        writeln!(
            output,
            r#"pub const {}: &[u8] = include_bytes!("{}");"#,
            name,
            asset.to_string_lossy()
        )
        .unwrap();
    }

    println!("cargo:rerun-if-changed=assets/*");
}
