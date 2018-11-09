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

project(${CMAKE_PROJECT_NAME}-common)

set(sources
    allocators/base_allocator/base_allocator.cpp
    allocators/pool_allocator/pool_allocator.cpp
    archives/json_archive/json_archive.cpp
    archives/psar_archive/psar_archive.cpp
    components/map/format/chunk/chunk.cpp
    components/map/format/frame/frame.cpp
    components/map/format/grid/grid.cpp
    components/map/format/layer/layer.cpp
    components/map/format/map/map.cpp
    components/map/format/object/object.cpp
    components/map/format/point2/point2.cpp
    components/map/format/property/property.cpp
    components/map/format/terrain/terrain.cpp
    components/map/format/text/text.cpp
    components/map/format/tile/tile.cpp
    components/map/format/tileset/tileset.cpp
    components/map/format/wang_color/wang_color.cpp
    components/map/format/wang_set/wang_set.cpp
    components/map/format/wang_tile/wang_tile.cpp
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
    components/color/color.lua_api.cpp
    components/rect/rect.lua_api.cpp
    components/vec2/vec2.lua_api.cpp
    components/vec3/vec3.lua_api.cpp
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
    components/map/format/format.unittest.cpp
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

target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra>
    $<$<CXX_COMPILER_ID:MSVC>:/Wall>)

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
