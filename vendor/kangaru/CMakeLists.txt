FetchContent_Declare(
    kangaru_git
    GIT_REPOSITORY https://github.com/gracicot/kangaru.git
    GIT_TAG 4852a2e6ded718fefc3cc94c32eaa6e54692e332)
FetchContent_GetProperties(kangaru_git)
if(NOT kangaru_git_POPULATED)
    FetchContent_Populate(kangaru_git)
    check_git_commit_hash(kangaru ${kangaru_git_SOURCE_DIR} master)
endif()

set(KANGARU_INSTALL
    OFF
    CACHE BOOL "")
set(KANGARU_EXPORT
    OFF
    CACHE BOOL "")
add_subdirectory(${kangaru_git_SOURCE_DIR} ${kangaru_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(system_libs
    kangaru)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_kangaru "" "" "${system_libs}")
