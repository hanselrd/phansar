CPMAddPackage(
    NAME pybind11
    GITHUB_REPOSITORY pybind/pybind11 # master
    GIT_TAG 9c0aa69937dbb9d7023123d5d98914855432982c)

# cmake-format: off
set(system_libs
    pybind11::embed)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_pybind11
    ""
    ""
    "${system_libs}")
