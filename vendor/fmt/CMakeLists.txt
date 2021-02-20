CPMAddPackage(
    NAME fmt
    GITHUB_REPOSITORY fmtlib/fmt # master
    GIT_TAG ab0f7d7fdcb46f35719197f7cae012fe843ec6a1)

# cmake-format: off
set(system_libs
    fmt)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_fmt
    ""
    ""
    "${system_libs}")
