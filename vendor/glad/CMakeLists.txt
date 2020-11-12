FetchContent_Declare(
    glad_git
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG b5d260b65b3edbbd9e75f5a6c9924fe0ff4f04dd)
FetchContent_GetProperties(glad_git)
if(NOT glad_git_POPULATED)
    FetchContent_Populate(glad_git)
    check_git_commit_hash(glad ${glad_git_SOURCE_DIR} master)
endif()

set(GLAD_PROFILE
    "core"
    CACHE STRING "")
set(GLAD_API
    "gl=3.3"
    CACHE STRING "")
set(GLAD_REPRODUCIBLE
    ON
    CACHE BOOL "")
add_subdirectory(${glad_git_SOURCE_DIR} ${glad_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(system_libs
    glad)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_glad "" "" "${system_libs}")
