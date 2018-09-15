project(common)

set(sources
    allocators/base.cpp
    allocators/pool_allocator.cpp
    archives/json_archive.cpp
    archives/psar_archive.cpp
    bitmasks/bitmasks.cpp
    core/core.cpp
    core/crypto.cpp
    core/dispatch_queue.cpp
    core/filesystem.cpp
    core/log.cpp
    core/serialize.cpp
    core/types.cpp
    models/models.cpp
    network/address.cpp
    network/socket.cpp
    scopes/enet_scope.cpp
    scopes/plibsys_scope.cpp
    scopes/sdl_scope.cpp
    common.cpp)

set(libs
    Threads::Threads
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    extlibs)

add_library(${PROJECT_NAME} STATIC
    ${sources})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${libs})
