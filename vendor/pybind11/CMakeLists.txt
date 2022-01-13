CPMAddPackage(
    NAME pybind11
    GITHUB_REPOSITORY pybind/pybind11 # master
    GIT_TAG f8d4aa47b6d9ffc7487d35598099971eb147d0ff
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_pybind11
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE pybind11::embed)
