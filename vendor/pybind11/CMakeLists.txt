CPMAddPackage(
    NAME pybind11
    GITHUB_REPOSITORY pybind/pybind11 # master
    GIT_TAG e25b1505dbca042289c4076141092cff49b0b96b
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_pybind11
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE pybind11::embed)
