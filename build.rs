fn main() {
    let cargo_manifest_dir = std::env::var("CARGO_MANIFEST_DIR").unwrap();
    let cargo_pkg_name = std::env::var("CARGO_PKG_NAME").unwrap();
    let cargo_pkg_version = std::env::var("CARGO_PKG_VERSION").unwrap();
    let out_dir = std::env::var("OUT_DIR").unwrap();

    let output = std::process::Command::new("git")
        .arg("rev-parse")
        .arg("--abbrev-ref")
        .arg("HEAD")
        .current_dir(&cargo_manifest_dir)
        .output()
        .unwrap();

    assert!(output.status.success());

    let git_branch = String::from_utf8_lossy(&output.stdout).trim().to_string();

    let output = std::process::Command::new("git")
        .arg("rev-parse")
        .arg("--short")
        .arg("HEAD")
        .current_dir(&cargo_manifest_dir)
        .output()
        .unwrap();

    assert!(output.status.success());

    let git_hash = String::from_utf8_lossy(&output.stdout).trim().to_string();

    let output = std::process::Command::new("git")
        .arg("diff")
        .arg("--quiet")
        .arg("--exit-code")
        .current_dir(&cargo_manifest_dir)
        .output()
        .unwrap();

    let git_changes = if !output.status.success() { "+" } else { "" };

    println!(
        "cargo:rustc-env=VERSION={}",
        format!(
            "{} {} ({}:{}{}, {} build, {} [{}], {})",
            cargo_pkg_name,
            cargo_pkg_version,
            git_branch,
            git_hash,
            git_changes,
            if cfg!(debug_assertions) {
                "debug"
            } else {
                "release"
            },
            std::env::consts::OS,
            std::env::consts::ARCH,
            chrono::Utc::now().format("%Y-%m-%dT%TZ")
        )
    );

    println!("cargo:rerun-if-changed=assets/*");

    let out_dir = std::path::PathBuf::from(out_dir);

    fs_extra::copy_items(
        &["assets"],
        out_dir,
        &fs_extra::dir::CopyOptions {
            overwrite: true,
            ..Default::default()
        },
    )
    .unwrap();
}
