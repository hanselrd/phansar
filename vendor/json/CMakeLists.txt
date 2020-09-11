FetchContent_Declare(
    json_git
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG 350ff4f7ced7c4117eae2fb93df02823c8021fcb)
FetchContent_GetProperties(json_git)
if(NOT json_git_POPULATED)
    FetchContent_Populate(json_git)
    check_git_commit_hash(json ${json_git_SOURCE_DIR} master)
endif()

set(JSON_BuildTests
    OFF
    CACHE BOOL "")
add_subdirectory(${json_git_SOURCE_DIR} ${json_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(system_libs
    nlohmann_json)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_json "" "" "${system_libs}")
