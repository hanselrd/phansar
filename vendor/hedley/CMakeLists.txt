CPMAddPackage(
    NAME hedley
    GITHUB_REPOSITORY nemequ/hedley # master
    GIT_TAG 8fb0604a8095f6c907378cc3f0391520ae843f6f
    DOWNLOAD_ONLY YES)

ph_add_library(
    NAME ph_vendor_hedley
    TYPE INTERFACE
    INCLUDE_DIRECTORIES INTERFACE ${hedley_SOURCE_DIR})
