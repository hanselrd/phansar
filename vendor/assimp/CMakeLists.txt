FetchContent_Declare(
    assimp_git
    GIT_REPOSITORY https://github.com/assimp/assimp.git
    GIT_TAG c50517d8df483de3b684a25b4d80b45bdb199aae)
FetchContent_GetProperties(assimp_git)
if(NOT assimp_git_POPULATED)
    FetchContent_Populate(assimp_git)
    check_git_commit_hash(assimp ${assimp_git_SOURCE_DIR} master)
endif()

set(BUILD_SHARED_LIBS
    OFF
    CACHE BOOL "")
set(ASSIMP_BUILD_ZLIB
    OFF
    CACHE BOOL "")
set(ASSIMP_BUILD_ASSIMP_TOOLS
    OFF
    CACHE BOOL "")
set(ASSIMP_BUILD_TESTS
    OFF
    CACHE BOOL "")
set(ASSIMP_INSTALL
    OFF
    CACHE BOOL "")
set(ASSIMP_INJECT_DEBUG_POSTFIX
    OFF
    CACHE BOOL "")
set(ASSIMP_IGNORE_GIT_HASH
    OFF
    CACHE BOOL "")
add_subdirectory(${assimp_git_SOURCE_DIR} ${assimp_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(system_libs
    assimp)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_assimp "" "" "${system_libs}")
