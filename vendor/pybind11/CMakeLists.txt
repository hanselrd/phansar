CPMAddPackage(
    NAME pybind11
    GITHUB_REPOSITORY pybind/pybind11 # master
    GIT_TAG c0fbb02c9fc1fe969f2740253469499385e6dc20)

# cmake-format: off
set(system_libs
    pybind11::embed)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_pybind11
    ""
    ""
    "${system_libs}")
