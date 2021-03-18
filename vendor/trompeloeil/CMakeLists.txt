CPMAddPackage(
    NAME trompeloeil
    GITHUB_REPOSITORY rollbear/trompeloeil # master
    GIT_TAG 858f5f12d02a5b4194b5ad28c012b2479312fc09)

# cmake-format: off
set(system_libs
    trompeloeil)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_trompeloeil
    ""
    ""
    "${system_libs}")
