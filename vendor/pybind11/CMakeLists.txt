CPMAddPackage(
    NAME pybind11
    GITHUB_REPOSITORY pybind/pybind11 # master
    GIT_TAG 0e01c243c7ffae3a2e52f998bacfe82f56aa96d9)

# cmake-format: off
set(system_libs
    pybind11::embed)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_pybind11
    ""
    ""
    "${system_libs}")
