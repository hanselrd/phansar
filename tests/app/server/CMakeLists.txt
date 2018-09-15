project(test-${CMAKE_PROJECT_NAME}-server)

set(sources
    lua_api.unit.cpp
    ../../main.cpp)

set(libs
    ${CMAKE_PROJECT_NAME}-server-test)

add_executable(${PROJECT_NAME}
    ${sources})

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${libs})

catch_discover_tests(${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
