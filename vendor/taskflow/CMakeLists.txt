CPMAddPackage(
    NAME taskflow
    GITHUB_REPOSITORY taskflow/taskflow # master
    GIT_TAG 0ca3b265eb840349ba169e246cdd5a0ec7f6bed3
    OPTIONS "TF_BUILD_TESTS OFF" "TF_BUILD_EXAMPLES OFF"
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_taskflow
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE Taskflow)
