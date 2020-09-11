FetchContent_Declare(
    plibsys_git
    GIT_REPOSITORY https://github.com/saprykin/plibsys.git
    GIT_TAG 1631fe68f048f81f749645aae3e56d9d0c544a0a)
FetchContent_GetProperties(plibsys_git)
if(NOT plibsys_git_POPULATED)
    FetchContent_Populate(plibsys_git)
    check_git_commit_hash(plibsys ${plibsys_git_SOURCE_DIR} master)
endif()

set(PLIBSYS_TESTS
    OFF
    CACHE BOOL "")
set(PLIBSYS_BUILD_DOC
    OFF
    CACHE BOOL "")
set(CMAKE_POLICY_DEFAULT_CMP0048 NEW)
add_subdirectory(${plibsys_git_SOURCE_DIR} ${plibsys_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(system_libs
    plibsysstatic)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_plibsys "" "" "${system_libs}")
