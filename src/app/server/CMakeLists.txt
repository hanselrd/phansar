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

project(${CMAKE_PROJECT_NAME}-server)

set(sources
    null.cpp)

set(libs
    common)

add_executable(${PROJECT_NAME}
    ${sources}
    main.cpp)

target_link_libraries(${PROJECT_NAME}
    ${libs})

add_library(${PROJECT_NAME}-test STATIC
    ${sources})

target_include_directories(${PROJECT_NAME}-test PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}-test PUBLIC
    ${libs})
