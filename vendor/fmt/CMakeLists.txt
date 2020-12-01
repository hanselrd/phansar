FetchContent_Declare(
    fmt_git
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 5a493560f59369e9fa664e8945b8e8a8ec4391b2)
FetchContent_GetProperties(fmt_git)
if(NOT fmt_git_POPULATED)
    FetchContent_Populate(fmt_git)
    check_git_commit_hash(fmt ${fmt_git_SOURCE_DIR} master)
endif()

add_subdirectory(${fmt_git_SOURCE_DIR} ${fmt_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(system_libs
    fmt)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_fmt "" "" "${system_libs}")
