CPMAddPackage(
    NAME fmt
    GITHUB_REPOSITORY fmtlib/fmt # master
    GIT_TAG 95da4847274c42c110fd5bf1bf61d3f94be4a08e)

# cmake-format: off
set(system_libs
    fmt)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_fmt
    ""
    ""
    "${system_libs}")
