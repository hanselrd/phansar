CPMAddPackage(
    NAME fmt
    GITHUB_REPOSITORY fmtlib/fmt # master
    GIT_TAG 578874033aeb12320f0d27eaa4f7bd02ce3aa4ee)

# cmake-format: off
set(system_libs
    fmt)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_fmt
    ""
    ""
    "${system_libs}")
