FetchContent_Declare(
    stb_git
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG b42009b3b9d4ca35bc703f5310eedc74f584be58)
FetchContent_GetProperties(stb_git)
if(NOT stb_git_POPULATED)
    FetchContent_Populate(stb_git)
    check_git_commit_hash(stb ${stb_git_SOURCE_DIR} master)
endif()

# add_subdirectory(${stb_git_SOURCE_DIR} ${stb_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(sources
    stb_image.cpp)

set(includes
    ${stb_git_SOURCE_DIR})
# cmake-format: on

ph_add_generic_vendor_library(ph_vendor_stb "${sources}" "${includes}" "" "")
