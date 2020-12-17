FetchContent_Declare(
    range_v3_git
    GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
    GIT_TAG d098b9610ac2f182f667ae9274ac2fac7f1327f5)
FetchContent_GetProperties(range_v3_git)
if(NOT range_v3_git_POPULATED)
    FetchContent_Populate(range_v3_git)
    check_git_commit_hash(range-v3 ${range_v3_git_SOURCE_DIR} master)
endif()

add_subdirectory(${range_v3_git_SOURCE_DIR} ${range_v3_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(system_libs
    range-v3)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_rangev3 "" "" "${system_libs}")
