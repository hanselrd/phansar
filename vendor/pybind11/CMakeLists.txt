FetchContent_Declare(
    pybind11_git
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG 17c22b9e0f56276f212b44f6cf0e6846a01623b2)
FetchContent_GetProperties(pybind11_git)
if(NOT pybind11_git_POPULATED)
    FetchContent_Populate(pybind11_git)
    check_git_commit_hash(pybind11 ${pybind11_git_SOURCE_DIR} master)
endif()

add_subdirectory(${pybind11_git_SOURCE_DIR} ${pybind11_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(system_libs
    pybind11::embed)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_pybind11 "" "" "${system_libs}")
