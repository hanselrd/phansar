FetchContent_Declare(sdl2_cmake_modules_git
    GIT_REPOSITORY https://github.com/aminosbh/sdl2-cmake-modules.git
    GIT_TAG        ad006a3daae65a612ed87415037e32188b81071e)
FetchContent_GetProperties(sdl2_cmake_modules_git)
if(NOT sdl2_cmake_modules_git_POPULATED)
    FetchContent_Populate(sdl2_cmake_modules_git)
    check_git_commit_hash(sdl2-cmake-modules ${sdl2_cmake_modules_git_SOURCE_DIR} master)
endif()

# add_subdirectory(${sdl2_cmake_modules_git_SOURCE_DIR} ${sdl2_cmake_modules_git_BINARY_DIR} EXCLUDE_FROM_ALL)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${sdl2_cmake_modules_git_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} PARENT_SCOPE)
