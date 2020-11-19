FetchContent_Declare(
    hedley_git
    GIT_REPOSITORY https://github.com/nemequ/hedley
    GIT_TAG 4a59eb6d8e3e73b6c60aed2c92a6590d26df93d8)
FetchContent_GetProperties(hedley_git)
if(NOT hedley_git_POPULATED)
    FetchContent_Populate(hedley_git)
    check_git_commit_hash(hedley ${hedley_git_SOURCE_DIR} master)
endif()

# add_subdirectory(${hedley_git_SOURCE_DIR} ${hedley_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(includes
    ${hedley_git_SOURCE_DIR})
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_hedley "${includes}" "" "")
