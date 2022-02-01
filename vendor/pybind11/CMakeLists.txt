CPMAddPackage(
    NAME pybind11
    GITHUB_REPOSITORY pybind/pybind11 # master
    GIT_TAG ce18721d830a9deb8cf1883b513bcb8f98090c35
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_pybind11
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE pybind11::embed)
