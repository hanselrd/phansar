project(test-common)

set(sources
    ../../main.cpp
    crypto.unit.cpp
    filesystem.unit.cpp
    lua_api.unit.cpp
    serialize.unit.cpp)

set(libs
    common)

add_executable(${PROJECT_NAME}
    ${sources})

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${libs})

catch_discover_tests(${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
