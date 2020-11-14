FetchContent_Declare(
    enet_git
    GIT_REPOSITORY https://github.com/lsalzman/enet.git
    GIT_TAG 4de13a2c2e98845f681c6e6221dc444877bd1cb7)
FetchContent_GetProperties(enet_git)
if(NOT enet_git_POPULATED)
    FetchContent_Populate(enet_git)
    check_git_commit_hash(enet ${enet_git_SOURCE_DIR} master)
endif()

set(CMAKE_POLICY_DEFAULT_CMP0048 NEW)
add_subdirectory(${enet_git_SOURCE_DIR} ${enet_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(includes
    ${enet_git_SOURCE_DIR}/include)

set(system_libs
    enet)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_enet "${includes}" "" "${system_libs}")
