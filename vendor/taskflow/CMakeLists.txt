CPMAddPackage(
    NAME taskflow
    GITHUB_REPOSITORY taskflow/taskflow # master
    GIT_TAG 20ae7ebbfd602c6c645bdf1df03a19d50657e316
    OPTIONS "TF_BUILD_TESTS OFF" "TF_BUILD_EXAMPLES OFF"
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_taskflow
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE Taskflow)
