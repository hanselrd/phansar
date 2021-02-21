CPMAddPackage(
    NAME cxxopts
    GITHUB_REPOSITORY jarro2783/cxxopts # master
    GIT_TAG dd45a0801c99d62109aaa29f8c410ba8def2fbf2)

# cmake-format: off
set(system_libs
    cxxopts)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_cxxopts
    ""
    ""
    "${system_libs}")
