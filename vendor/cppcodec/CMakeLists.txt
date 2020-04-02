FetchContent_Declare(cppcodec_git
    GIT_REPOSITORY https://github.com/tplgy/cppcodec.git
    GIT_TAG        bd6ddf95129e769b50ef63e0f558fa21364f3f65)
FetchContent_GetProperties(cppcodec_git)
if(NOT cppcodec_git_POPULATED)
    FetchContent_Populate(cppcodec_git)
    check_git_commit_hash(cppcodec ${cppcodec_git_SOURCE_DIR} master)
endif()

# add_subdirectory(${cppcodec_git_SOURCE_DIR} ${cppcodec_git_BINARY_DIR} EXCLUDE_FROM_ALL)

set(includes
    ${cppcodec_git_SOURCE_DIR})

ph_add_generic_vendor_interface_library(ph_vendor_cppcodec "${includes}" "" "")
