CPMAddPackage(
    NAME fmt
    GITHUB_REPOSITORY fmtlib/fmt # master
    GIT_TAG d8e1c9f175a363e7cfe8ff340df2f77d682bc344)

# cmake-format: off
set(system_libs
    fmt)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_fmt
    ""
    ""
    "${system_libs}")
