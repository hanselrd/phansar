FetchContent_Declare(
    libpqxx_git
    GIT_REPOSITORY https://github.com/jtv/libpqxx.git
    GIT_TAG 7eed2f24df244f3987b5845be8650008aa953cc4)
FetchContent_GetProperties(libpqxx_git)
if(NOT libpqxx_git_POPULATED)
    FetchContent_Populate(libpqxx_git)
    check_git_commit_hash(libpqxx ${libpqxx_git_SOURCE_DIR} master)
endif()

set(SKIP_BUILD_TEST
    ON
    CACHE BOOL "")
add_subdirectory(${libpqxx_git_SOURCE_DIR} ${libpqxx_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(system_libs
    pqxx)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_libpqxx "" "" "${system_libs}")
