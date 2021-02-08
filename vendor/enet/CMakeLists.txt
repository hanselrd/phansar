FetchContent_Declare(
    enet_git
    GIT_REPOSITORY https://github.com/lsalzman/enet.git
    GIT_TAG e3ada4ed750b976833e3d54a9c1179445289bbf6)
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
if(WIN32)
    set(system_libs
        ${system_libs}
        ws2_32
        winmm)
endif()
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_enet "${includes}" "" "${system_libs}")
