FetchContent_Declare(
    entt_git
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG 18832fcb3765e02e66b033a0cf723683762463c0)
FetchContent_GetProperties(entt_git)
if(NOT entt_git_POPULATED)
    FetchContent_Populate(entt_git)
    check_git_commit_hash(entt ${entt_git_SOURCE_DIR} master)
endif()

# add_subdirectory(${entt_git_SOURCE_DIR} ${entt_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(includes
    ${entt_git_SOURCE_DIR}/single_include)
# cmake-format: on

ph_add_generic_vendor_interface_library(ph_vendor_entt "${includes}" "" "")
