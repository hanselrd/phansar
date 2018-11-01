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

project(${CMAKE_PROJECT_NAME})

set(sources
    graphics/circle/circle.cpp
    graphics/polygon/polygon.cpp
    graphics/rectangle/rectangle.cpp
    graphics/shape/shape.cpp
    graphics/text/text.cpp
    graphics/triangle/triangle.cpp
    managees/resource/loader/loader.cpp
    managers/input_manager/input_manager.cpp
    managers/resource_manager/resource_manager.cpp
    managers/system_manager/system_manager.cpp
    ui/element/element.cpp
    ui/panel/panel.cpp
    ui/window/window.cpp)

set(lua_api_sources
    lua_api/lua_api.cpp)

set(unittest_sources
    lua_api/lua_api.unittest.cpp)

set(libs
    common)

add_executable(${PROJECT_NAME}
    ${sources}
    ${lua_api_sources}
    main.cpp)

target_link_libraries(${PROJECT_NAME}
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
    TESTING_CLIENT)

catch_discover_tests(test-${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
