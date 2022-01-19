CPMAddPackage(
    NAME taskflow
    GITHUB_REPOSITORY taskflow/taskflow # master
    GIT_TAG f8990db37a9fcead38d47725d5013babcf8f9cdf
    OPTIONS "TF_BUILD_TESTS OFF" "TF_BUILD_EXAMPLES OFF"
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_taskflow
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE Taskflow)
