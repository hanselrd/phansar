CPMAddPackage(
    NAME pybind11
    GITHUB_REPOSITORY pybind/pybind11 # master
    GIT_TAG ad6bf5cd39ca64b4a9bf846b84b11c4c8df1c8e1)

# cmake-format: off
set(system_libs
    pybind11::embed)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_pybind11
    ""
    ""
    "${system_libs}")
