FetchContent_Declare(
    bgfx_git
    GIT_REPOSITORY https://github.com/widberg/bgfx.cmake.git
    GIT_TAG 66f18daf5c380b34f4745ac0922b8a9853b51ad9)
FetchContent_GetProperties(bgfx_git)
if(NOT bgfx_git_POPULATED)
    FetchContent_Populate(bgfx_git)
    check_git_commit_hash(bgfx ${bgfx_git_SOURCE_DIR} master)
endif()

add_subdirectory(${bgfx_git_SOURCE_DIR} ${bgfx_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(system_libs
    bgfx)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_bgfx "" "" "${system_libs}")
