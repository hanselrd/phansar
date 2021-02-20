CPMAddPackage(
    NAME trompeloeil
    GITHUB_REPOSITORY rollbear/trompeloeil # master
    GIT_TAG 38d1c074a2fd8731b1d94dd059f2ae36a6adcc27)

# cmake-format: off
set(system_libs
    trompeloeil)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_trompeloeil
    ""
    ""
    "${system_libs}")
