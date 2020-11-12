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
add_subdirectory(docopt.cpp EXCLUDE_FROM_ALL)
add_subdirectory(enet EXCLUDE_FROM_ALL)
add_subdirectory(entt EXCLUDE_FROM_ALL)
add_subdirectory(fmt EXCLUDE_FROM_ALL)
add_subdirectory(glad EXCLUDE_FROM_ALL)
add_subdirectory(glfw EXCLUDE_FROM_ALL)
add_subdirectory(hedley EXCLUDE_FROM_ALL)
add_subdirectory(json EXCLUDE_FROM_ALL)
add_subdirectory(libpqxx EXCLUDE_FROM_ALL)
add_subdirectory(pybind11 EXCLUDE_FROM_ALL)
add_subdirectory(range-v3 EXCLUDE_FROM_ALL)
add_subdirectory(stb EXCLUDE_FROM_ALL)
add_subdirectory(taskflow EXCLUDE_FROM_ALL)
add_subdirectory(trompeloeil EXCLUDE_FROM_ALL)
add_subdirectory(xsimd EXCLUDE_FROM_ALL)

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    PARENT_SCOPE)
