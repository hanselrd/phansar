CPMAddPackage(
    NAME xsimd
    GITHUB_REPOSITORY xtensor-stack/xsimd # master
    GIT_TAG ccf4ff93a82d90fc7868e17d1ca785f5e13fef5d)

# cmake-format: off
set(system_libs
    xsimd)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_xsimd
    ""
    ""
    "${system_libs}")
