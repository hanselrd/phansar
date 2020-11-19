FetchContent_Declare(
    json_git
    GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent.git
    GIT_TAG v3.9.1)
FetchContent_GetProperties(json_git)
if(NOT json_git_POPULATED)
    FetchContent_Populate(json_git)
    check_git_commit_hash(json ${json_git_SOURCE_DIR} master)
endif()

set(JSON_BuildTests
    OFF
    CACHE BOOL "")
set(JSON_ImplicitConversions
    OFF
    CACHE BOOL "")
add_subdirectory(${json_git_SOURCE_DIR} ${json_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(system_libs
    nlohmann_json)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_json "" "" "${system_libs}")
