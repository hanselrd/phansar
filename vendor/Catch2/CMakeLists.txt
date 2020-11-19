FetchContent_Declare(
    Catch2_git
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG 578f8b80068d5cb578e271e4ccb01a59117a9733)
FetchContent_GetProperties(Catch2_git)
if(NOT catch2_git_POPULATED)
    FetchContent_Populate(Catch2_git)
    check_git_commit_hash(Catch2 ${catch2_git_SOURCE_DIR} v2.x)
endif()

set(CATCH_BUILD_TESTING
    OFF
    CACHE BOOL "")
set(CATCH_INSTALL_DOCS
    OFF
    CACHE BOOL "")
set(CATCH_INSTALL_HELPERS
    OFF
    CACHE BOOL "")
add_subdirectory(${catch2_git_SOURCE_DIR} ${catch2_git_BINARY_DIR} EXCLUDE_FROM_ALL)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${catch2_git_SOURCE_DIR}/contrib)
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    PARENT_SCOPE)

# cmake-format: off
set(system_libs
    Catch2)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_catch2 "" "" "${system_libs}")
