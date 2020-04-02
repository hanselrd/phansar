FetchContent_Declare(json_git
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        456478b3c50d60100dbb1fb9bc931f370a2c1c28)
FetchContent_GetProperties(json_git)
if(NOT json_git_POPULATED)
    FetchContent_Populate(json_git)
    check_git_commit_hash(json ${json_git_SOURCE_DIR} master)
endif()

set(JSON_BuildTests OFF CACHE BOOL "")
add_subdirectory(${json_git_SOURCE_DIR} ${json_git_BINARY_DIR} EXCLUDE_FROM_ALL)

set(system_libs
    nlohmann_json)

ph_add_generic_vendor_interface_library(ph_vendor_json "" "" "${system_libs}")
