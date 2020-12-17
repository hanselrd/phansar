FetchContent_Declare(
    glm_git
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG bfd439bea51fe0f4d4b9d813f7765025a52fa27a)
FetchContent_GetProperties(glm_git)
if(NOT glm_git_POPULATED)
    FetchContent_Populate(glm_git)
    check_git_commit_hash(glm ${glm_git_SOURCE_DIR} master)
endif()

add_subdirectory(${glm_git_SOURCE_DIR} ${glm_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(system_libs
    glm)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_glm "" "" "${system_libs}")
