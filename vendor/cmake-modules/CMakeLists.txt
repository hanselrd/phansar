FetchContent_Declare(
    cmake_modules_git
    GIT_REPOSITORY https://github.com/rpavlik/cmake-modules.git
    GIT_TAG 6a748896188fdf3f885820ccd686393ea5215dbf)
FetchContent_GetProperties(cmake_modules_git)
if(NOT cmake_modules_git_POPULATED)
    FetchContent_Populate(cmake_modules_git)
    check_git_commit_hash(cmake-modules ${cmake_modules_git_SOURCE_DIR} main)
endif()

# add_subdirectory(${cmake_modules_git_SOURCE_DIR} ${cmake_modules_git_BINARY_DIR} EXCLUDE_FROM_ALL)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${cmake_modules_git_SOURCE_DIR})
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    PARENT_SCOPE)
