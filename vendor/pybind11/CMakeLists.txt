CPMAddPackage(
    NAME pybind11
    GITHUB_REPOSITORY pybind/pybind11 # master
    GIT_TAG 9ec1128c7aac3d069a4ec2bd1dfc7f57c6526d1c
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_pybind11
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE pybind11::embed)
