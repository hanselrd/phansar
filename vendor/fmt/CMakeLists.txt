CPMAddPackage(
    NAME fmt
    GITHUB_REPOSITORY fmtlib/fmt # master
    GIT_TAG 52bd62c72f6c15dcfaee237df09cdafd9a990fc3
    EXCLUDE_FROM_ALL YES)

# cmake-format: off
set(system_libs
    fmt)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_fmt
    ""
    ""
    "${system_libs}")
