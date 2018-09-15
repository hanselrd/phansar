project(test-common)

set(sources
    allocators/pool_allocator.unit.cpp
    core/crypto.unit.cpp
    core/dispatch_queue.unit.cpp
    core/filesystem.unit.cpp
    core/serialize.unit.cpp
    scopes/enet_scope.unit.cpp
    scopes/plibsys_scope.unit.cpp
    scopes/sdl_scope.unit.cpp
    lua_api.unit.cpp
    ../../main.cpp)

set(libs
    common)

add_executable(${PROJECT_NAME}
    ${sources})

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${libs})

catch_discover_tests(${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
