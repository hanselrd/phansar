FetchContent_Declare(
    pybind11_git
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG a54eab92d265337996b8e4b4149d9176c2d428a6)
FetchContent_GetProperties(pybind11_git)
if(NOT pybind11_git_POPULATED)
    FetchContent_Populate(pybind11_git)
    check_git_commit_hash(pybind11 ${pybind11_git_SOURCE_DIR} master)
endif()

add_subdirectory(${pybind11_git_SOURCE_DIR} ${pybind11_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(system_libs
    pybind11::pybind11)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_pybind11 "" "" "${system_libs}")

target_link_libraries(ph_vendor_pybind11 INTERFACE ${PYTHON_LIBRARIES})
