project(vendor)

find_package(Git REQUIRED)

function(check_git_commit_hash name source_dir branch)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
        OUTPUT_VARIABLE head_hash
        WORKING_DIRECTORY ${source_dir})

    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse origin/${branch}
        OUTPUT_VARIABLE origin_hash
        WORKING_DIRECTORY ${source_dir})

    message(STATUS "${name}: ${source_dir}")
    message(STATUS "${name}: (HEAD) ${head_hash}")

    if(NOT ${head_hash} STREQUAL ${origin_hash})
        message(WARNING "Newer commit ${name}: (origin/${branch}) ${origin_hash}")
    endif()
endfunction()

include(FetchContent)
FetchContent_Declare(Catch2_git
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        62609621088df6723e48ea1d164108303511755b)
FetchContent_GetProperties(Catch2_git)
if(NOT catch2_git_POPULATED)
    FetchContent_Populate(Catch2_git)
    check_git_commit_hash(Catch2 ${catch2_git_SOURCE_DIR} master)
endif()

set(CATCH_BUILD_TESTING OFF CACHE BOOL "")
set(CATCH_INSTALL_DOCS OFF CACHE BOOL "")
set(CATCH_INSTALL_HELPERS OFF CACHE BOOL "")
add_subdirectory(${catch2_git_SOURCE_DIR} ${catch2_git_BINARY_DIR} EXCLUDE_FROM_ALL)

FetchContent_Declare(plibsys_git
    GIT_REPOSITORY https://github.com/saprykin/plibsys.git
    GIT_TAG        e57dfc613163989bb536d980bec142fd7e35271d)
FetchContent_GetProperties(plibsys_git)
if(NOT plibsys_git_POPULATED)
    FetchContent_Populate(plibsys_git)
    check_git_commit_hash(plibsys ${plibsys_git_SOURCE_DIR} master)
endif()

set(PLIBSYS_TESTS OFF CACHE BOOL "")
set(PLIBSYS_BUILD_DOC OFF CACHE BOOL "")
add_subdirectory(${plibsys_git_SOURCE_DIR} ${plibsys_git_BINARY_DIR} EXCLUDE_FROM_ALL)

FetchContent_Declare(sdl2_cmake_modules_git
    GIT_REPOSITORY https://github.com/aminosbh/sdl2-cmake-modules.git
    GIT_TAG        ad006a3daae65a612ed87415037e32188b81071e)
FetchContent_GetProperties(sdl2_cmake_modules_git)
if(NOT sdl2_cmake_modules_git_POPULATED)
    FetchContent_Populate(sdl2_cmake_modules_git)
    check_git_commit_hash(sdl2-cmake-modules ${sdl2_cmake_modules_git_SOURCE_DIR} master)
endif()

FetchContent_Declare(spdlog_git
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        f57378d8ba5757837b913a3d4b059b9c54a43ee1)
FetchContent_GetProperties(spdlog_git)
if(NOT spdlog_git_POPULATED)
    FetchContent_Populate(spdlog_git)
    check_git_commit_hash(spdlog ${spdlog_git_SOURCE_DIR} v1.x)
endif()

add_subdirectory(${spdlog_git_SOURCE_DIR} ${spdlog_git_BINARY_DIR} EXCLUDE_FROM_ALL)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${sdl2_cmake_modules_git_SOURCE_DIR} ${catch2_git_SOURCE_DIR}/contrib PARENT_SCOPE)

set(libs
    plibsysstatic
    spdlog)

ph_add_generic_interface_library(ph_vendor "${libs}")
