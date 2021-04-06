CPMAddPackage(
    NAME xsimd
    GITHUB_REPOSITORY xtensor-stack/xsimd # master
    GIT_TAG 1bd6d8c44e4e8536f94e853772d03be3847e7f43)

# cmake-format: off
set(system_libs
    xsimd)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_xsimd
    ""
    ""
    "${system_libs}")
