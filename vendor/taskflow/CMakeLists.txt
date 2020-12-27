FetchContent_Declare(
    taskflow_git
    GIT_REPOSITORY https://github.com/taskflow/taskflow.git
    GIT_TAG 2f66dde00cddeee37cdd6efb498297ff3872d495)
FetchContent_GetProperties(taskflow_git)
if(NOT taskflow_git_POPULATED)
    FetchContent_Populate(taskflow_git)
    check_git_commit_hash(taskflow ${taskflow_git_SOURCE_DIR} master)
endif()

set(TF_BUILD_TESTS
    OFF
    CACHE BOOL "")
set(TF_BUILD_EXAMPLES
    OFF
    CACHE BOOL "")
add_subdirectory(${taskflow_git_SOURCE_DIR} ${taskflow_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(system_libs
    Taskflow)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_taskflow "" "" "${system_libs}")
