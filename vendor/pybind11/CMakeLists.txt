CPMAddPackage(
    NAME pybind11
    GITHUB_REPOSITORY pybind/pybind11 # master
    GIT_TAG 3a1eddab54e48bd80cc167c242bc1d9f537498c1
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_pybind11
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE pybind11::embed)
