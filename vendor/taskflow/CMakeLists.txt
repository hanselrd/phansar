CPMAddPackage(
    NAME taskflow
    GITHUB_REPOSITORY taskflow/taskflow # master
    GIT_TAG 3e38094822e52b3d32a841454a035c4ea4ea1d8e
    OPTIONS "TF_BUILD_TESTS OFF" "TF_BUILD_EXAMPLES OFF"
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_taskflow
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE Taskflow)
