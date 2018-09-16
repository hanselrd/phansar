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
    allocators/base_allocator.cpp
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
