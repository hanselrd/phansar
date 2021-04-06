CPMAddPackage(
    NAME trompeloeil
    GITHUB_REPOSITORY rollbear/trompeloeil # master
    GIT_TAG 8ae997b36a0419063d1805a3400661b1e2eb4933)

# cmake-format: off
set(system_libs
    trompeloeil)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_trompeloeil
    ""
    ""
    "${system_libs}")
