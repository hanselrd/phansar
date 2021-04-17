CPMAddPackage(
    NAME xsimd
    GITHUB_REPOSITORY xtensor-stack/xsimd # master
    GIT_TAG 423ed6747e5e0f30842eb98adf10bd110d01cadf
    EXCLUDE_FROM_ALL YES)

# cmake-format: off
set(system_libs
    xsimd)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_xsimd
    ""
    ""
    "${system_libs}")
