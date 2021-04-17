CPMAddPackage(
    NAME pybind11
    GITHUB_REPOSITORY pybind/pybind11 # master
    GIT_TAG 114be7f4ade0ad798cd4c7f5d65ebe4ba8bd892d
    EXCLUDE_FROM_ALL YES)

# cmake-format: off
set(system_libs
    pybind11::embed)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_pybind11
    ""
    ""
    "${system_libs}")
