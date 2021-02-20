CPMAddPackage(
    NAME cppcodec
    GITHUB_REPOSITORY tplgy/cppcodec # master
    GIT_TAG bd6ddf95129e769b50ef63e0f558fa21364f3f65
    DOWNLOAD_ONLY YES)

# cmake-format: off
set(includes
    ${cppcodec_SOURCE_DIR})
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_cppcodec
    "${includes}"
    ""
    "")
