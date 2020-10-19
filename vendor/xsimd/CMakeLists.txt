FetchContent_Declare(
    xsimd_git
    GIT_REPOSITORY https://github.com/xtensor-stack/xsimd.git
    GIT_TAG ba4470b4c5e3028684bf71a5f0da335cfdb4d716)
FetchContent_GetProperties(xsimd_git)
if(NOT xsimd_git_POPULATED)
    FetchContent_Populate(xsimd_git)
    check_git_commit_hash(xsimd ${xsimd_git_SOURCE_DIR} master)
endif()

add_subdirectory(${xsimd_git_SOURCE_DIR} ${xsimd_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(system_libs
    xsimd)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_xsimd "" "" "${system_libs}")
