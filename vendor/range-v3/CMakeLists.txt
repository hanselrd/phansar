CPMAddPackage(
    NAME range-v3
    GITHUB_REPOSITORY ericniebler/range-v3 # master
    GIT_TAG 81b6d3f1bf636395645cc2ed245a5947c404a4b2)

# cmake-format: off
set(system_libs
    range-v3)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_rangev3
    ""
    ""
    "${system_libs}")
