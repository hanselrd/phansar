CPMAddPackage(
    NAME trompeloeil
    GITHUB_REPOSITORY rollbear/trompeloeil # master
    GIT_TAG 0ea31cfd8abdb3f59a09b7957883907c87442dd4)

# cmake-format: off
set(system_libs
    trompeloeil)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_trompeloeil
    ""
    ""
    "${system_libs}")
