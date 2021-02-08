FetchContent_Declare(
    trompeloeil_git
    GIT_REPOSITORY https://github.com/rollbear/trompeloeil.git
    GIT_TAG 38d1c074a2fd8731b1d94dd059f2ae36a6adcc27)
FetchContent_GetProperties(trompeloeil_git)
if(NOT trompeloeil_git_POPULATED)
    FetchContent_Populate(trompeloeil_git)
    check_git_commit_hash(trompeloeil ${trompeloeil_git_SOURCE_DIR} master)
endif()

add_subdirectory(${trompeloeil_git_SOURCE_DIR} ${trompeloeil_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(system_libs
    trompeloeil)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_trompeloeil "" "" "${system_libs}")
