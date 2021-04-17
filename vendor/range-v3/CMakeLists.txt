CPMAddPackage(
    NAME range-v3
    GITHUB_REPOSITORY ericniebler/range-v3 # master
    GIT_TAG 1120609c7cb5dee9d2d216c579e935475cc39c4e
    EXCLUDE_FROM_ALL YES)

# cmake-format: off
set(system_libs
    range-v3)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_rangev3
    ""
    ""
    "${system_libs}")
