FetchContent_Declare(
    sol2_git
    GIT_REPOSITORY https://github.com/ThePhD/sol2.git
    GIT_TAG 670ea9b4051a9e4114b10935df93e2780a3fa06b)
FetchContent_GetProperties(sol2_git)
if(NOT sol2_git_POPULATED)
    FetchContent_Populate(sol2_git)
    check_git_commit_hash(sol2 ${sol2_git_SOURCE_DIR} develop)
endif()

# add_subdirectory(${sol2_git_SOURCE_DIR} ${sol2_git_BINARY_DIR} EXCLUDE_FROM_ALL)

set(includes ${sol2_git_SOURCE_DIR}/single/include)

ph_add_generic_vendor_interface_library(ph_vendor_sol2 "${includes}" "" "")
