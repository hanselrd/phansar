FetchContent_Declare(
    raygui_git
    GIT_REPOSITORY https://github.com/raysan5/raygui.git
    GIT_TAG b73eb56f3c556a8f18279a6cc0f20b3956345001)
FetchContent_GetProperties(raygui_git)
if(NOT raygui_git_POPULATED)
    FetchContent_Populate(raygui_git)
    check_git_commit_hash(raygui ${raygui_git_SOURCE_DIR} master)
endif()

set(BUILD_RAYGUI_EXAMPLES
    OFF
    CACHE BOOL "")
add_subdirectory(${raygui_git_SOURCE_DIR}/projects/CMake ${raygui_git_BINARY_DIR} EXCLUDE_FROM_ALL)

# cmake-format: off
set(sources
    raygui.cpp)

set(libs
    ph_vendor_raylib)

set(system_libs
    raygui)
# cmake-format: on

ph_add_generic_vendor_library(ph_vendor_raygui "${sources}" "" "${libs}" "${system_libs}")
