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
