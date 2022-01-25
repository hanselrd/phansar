CPMAddPackage(
    NAME taskflow
    GITHUB_REPOSITORY taskflow/taskflow # master
    GIT_TAG f423a100a70b275f6e7331bc96537a3fe172e8d7
    OPTIONS "TF_BUILD_TESTS OFF" "TF_BUILD_EXAMPLES OFF"
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_taskflow
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE Taskflow)
