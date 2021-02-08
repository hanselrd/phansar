FetchContent_Declare(
    glfw_git
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 94773111300fee0453844a4c9407af7e880b4df8)
FetchContent_GetProperties(glfw_git)
if(NOT glfw_git_POPULATED)
    FetchContent_Populate(glfw_git)
    check_git_commit_hash(glfw ${glfw_git_SOURCE_DIR} master)
endif()

set(GLFW_BUILD_DOCS
    OFF
    CACHE BOOL "")
set(GLFW_INSTALL
    OFF
    CACHE BOOL "")
add_subdirectory(${glfw_git_SOURCE_DIR} ${glfw_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(system_libs
    glfw)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_glfw "" "" "${system_libs}")
