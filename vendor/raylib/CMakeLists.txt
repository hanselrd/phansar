FetchContent_Declare(
    raylib_git
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 00b31998590aafe9c03d54a0ebfb1b1fbb6795ce)
FetchContent_GetProperties(raylib_git)
if(NOT raylib_git_POPULATED)
    FetchContent_Populate(raylib_git)
    check_git_commit_hash(raylib ${raylib_git_SOURCE_DIR} master)
endif()

set(BUILD_EXAMPLES
    OFF
    CACHE BOOL "")
add_subdirectory(${raylib_git_SOURCE_DIR} ${raylib_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(system_libs
    raylib_static)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_raylib "" "" "${system_libs}")
