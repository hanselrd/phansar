#
# This file is part of Phansar.
#
# Copyright (C) 2018  Hansel De La Cruz
#
# Phansar is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Phansar is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with Phansar.  If not, see <http://www.gnu.org/licenses/>.
#

project(common)

set(sources
    allocators/base_allocator/base_allocator.cpp
    allocators/pool_allocator/pool_allocator.cpp
    archives/json_archive/json_archive.cpp
    archives/psar_archive/psar_archive.cpp
    containers/dispatch_queue/dispatch_queue.cpp
    network/address/address.cpp
    network/socket/socket.cpp
    scopes/enet_scope/enet_scope.cpp
    scopes/plibsys_scope/plibsys_scope.cpp
    scopes/sdl_scope/sdl_scope.cpp
    utils/log/log.cpp)

set(lua_api_sources
    bitmasks/permissions/permissions.lua_api.cpp
    bitmasks/bitmasks.lua_api.cpp
    components/vector2/vector2.lua_api.cpp
    components/vector3/vector3.lua_api.cpp
    components/components.lua_api.cpp
    lua_api/lua_api.cpp
    models/entity/entity.lua_api.cpp
    models/player/player.lua_api.cpp
    models/models.lua_api.cpp
    utils/log/log.lua_api.cpp
    utils/utils.lua_api.cpp)

set(unittest_sources
    allocators/pool_allocator/pool_allocator.unittest.cpp
    archives/json_archive/json_archive.unittest.cpp
    archives/psar_archive/psar_archive.unittest.cpp
    containers/dispatch_queue/dispatch_queue.unittest.cpp
    containers/event_queue/event_queue.unittest.cpp
    lua_api/lua_api.unittest.cpp
    scopes/enet_scope/enet_scope.unittest.cpp
    scopes/plibsys_scope/plibsys_scope.unittest.cpp
    scopes/sdl_scope/sdl_scope.unittest.cpp)

set(libs
    Threads::Threads
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    extlibs)

add_library(${PROJECT_NAME} STATIC
    ${sources}
    ${lua_api_sources})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${libs})

# Testing
add_executable(test-${PROJECT_NAME}
    ${sources}
    ${lua_api_sources}
    ${unittest_sources}
    ../../../tests/main.cpp)

target_link_libraries(test-${PROJECT_NAME} PUBLIC
    ${libs})

target_compile_definitions(test-${PROJECT_NAME} PRIVATE
    TESTING_COMMON)

catch_discover_tests(test-${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
