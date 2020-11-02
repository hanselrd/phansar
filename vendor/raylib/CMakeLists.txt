FetchContent_Declare(
    raylib_git
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 05ab39ed9f995fc5577fa72a0a5338eff2460cd8)
FetchContent_GetProperties(raylib_git)
if(NOT raylib_git_POPULATED)
    FetchContent_Populate(raylib_git)
    check_git_commit_hash(raylib ${raylib_git_SOURCE_DIR} master)
endif()

set(BUILD_EXAMPLES
    OFF
    CACHE BOOL "")
set(CMAKE_POLICY_DEFAULT_CMP0072 NEW)
add_subdirectory(${raylib_git_SOURCE_DIR} ${raylib_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(system_libs
    raylib_static)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_raylib "" "" "${system_libs}")
