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
        message(STATUS "Newer commit ${name}: (origin/${branch}) ${origin_hash}")
    endif()
endfunction()

add_subdirectory(Catch2 EXCLUDE_FROM_ALL)
add_subdirectory(cppcodec EXCLUDE_FROM_ALL)
add_subdirectory(json EXCLUDE_FROM_ALL)
add_subdirectory(lua EXCLUDE_FROM_ALL)
add_subdirectory(plibsys EXCLUDE_FROM_ALL)
add_subdirectory(sdl2-cmake-modules EXCLUDE_FROM_ALL)
add_subdirectory(sol2 EXCLUDE_FROM_ALL)
add_subdirectory(spdlog EXCLUDE_FROM_ALL)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} PARENT_SCOPE)

set(system_libs
    ph_vendor_cppcodec
    ph_vendor_json
    ph_vendor_lua
    ph_vendor_plibsys
    ph_vendor_sol2
    ph_vendor_spdlog)

ph_add_generic_interface_library(ph_vendor "" "${system_libs}")
