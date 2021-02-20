CPMAddPackage(
    NAME hedley
    GITHUB_REPOSITORY nemequ/hedley # master
    GIT_TAG 8fb0604a8095f6c907378cc3f0391520ae843f6f
    DOWNLOAD_ONLY YES)

# cmake-format: off
set(includes
    ${hedley_SOURCE_DIR})
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_hedley
    "${includes}"
    ""
    "")
