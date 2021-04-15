CPMAddPackage(
    NAME trompeloeil
    GITHUB_REPOSITORY rollbear/trompeloeil # master
    GIT_TAG 0e925c71f32ed5c0e9174f901014f8c54b7bc336)

# cmake-format: off
set(system_libs
    trompeloeil)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_trompeloeil
    ""
    ""
    "${system_libs}")
