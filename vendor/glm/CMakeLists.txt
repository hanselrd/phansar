FetchContent_Declare(
    glm_git
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 596577f2004fb36308a5afc277b1aaf2dc7cbb55)
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
