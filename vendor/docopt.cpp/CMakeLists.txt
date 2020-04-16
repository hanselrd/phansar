FetchContent_Declare(
    docopt_cpp_git
    GIT_REPOSITORY https://github.com/docopt/docopt.cpp.git
    GIT_TAG c8a63d5fa606091e5c8044bb7c2b1db3f51f100d)
FetchContent_GetProperties(docopt_cpp_git)
if(NOT docopt_cpp_git_POPULATED)
    FetchContent_Populate(docopt_cpp_git)
    check_git_commit_hash(docopt.cpp ${docopt_cpp_git_SOURCE_DIR} master)
endif()

add_subdirectory(${docopt_cpp_git_SOURCE_DIR} ${docopt_cpp_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(system_libs
    docopt_s)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_docopt "" "" "${system_libs}")
