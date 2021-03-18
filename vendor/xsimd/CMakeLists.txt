CPMAddPackage(
    NAME xsimd
    GITHUB_REPOSITORY xtensor-stack/xsimd # master
    GIT_TAG f48de3b1c3f1086fa3b29cdcef187d51b3d60408)

# cmake-format: off
set(system_libs
    xsimd)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_xsimd
    ""
    ""
    "${system_libs}")
