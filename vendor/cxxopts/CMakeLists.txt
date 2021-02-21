CPMAddPackage(
    NAME cxxopts
    GITHUB_REPOSITORY jarro2783/cxxopts # master
    GIT_TAG f34d6038635f52dc9dd05f35a6bf95469b18abe0)

# cmake-format: off
set(system_libs
    cxxopts)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_cxxopts
    ""
    ""
    "${system_libs}")
