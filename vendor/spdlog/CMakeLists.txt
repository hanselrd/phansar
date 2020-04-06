FetchContent_Declare(spdlog_git
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        ca9c83f824270a7ee1d183f29faa01262f810fd6)
FetchContent_GetProperties(spdlog_git)
if(NOT spdlog_git_POPULATED)
    FetchContent_Populate(spdlog_git)
    check_git_commit_hash(spdlog ${spdlog_git_SOURCE_DIR} v1.x)
endif()

add_subdirectory(${spdlog_git_SOURCE_DIR} ${spdlog_git_BINARY_DIR} EXCLUDE_FROM_ALL)

set(system_libs
    spdlog)

ph_add_generic_vendor_interface_library(ph_vendor_spdlog "" "" "${system_libs}")
