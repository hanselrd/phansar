FetchContent_Declare(
    spdlog_git
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG d09e03606cd4ca0c0dde835f1b26d0311bec37ff)
FetchContent_GetProperties(spdlog_git)
if(NOT spdlog_git_POPULATED)
    FetchContent_Populate(spdlog_git)
    check_git_commit_hash(spdlog ${spdlog_git_SOURCE_DIR} v1.x)
endif()

add_subdirectory(${spdlog_git_SOURCE_DIR} ${spdlog_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(system_libs
    spdlog)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_spdlog "" "" "${system_libs}")
