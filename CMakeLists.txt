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

cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

# Project settings
project(phansar VERSION 1.0.0 LANGUAGES CXX C)

# Include CMake Modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)

# Set configuration and output
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find Git
find_package(Git REQUIRED)

# Find Threads
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

# Find SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
if(SDL2_FOUND)
    include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS})
endif()

# Used in the logger to get relative path
string(LENGTH ${CMAKE_SOURCE_DIR}/src/ SOURCE_PATH_SIZE)
add_definitions(-D__SOURCE_PATH_SIZE__=${SOURCE_PATH_SIZE})

# Setup testing
enable_testing()
include(CTest)

# Build project
add_subdirectory(vendor)
include(Catch)
add_subdirectory(src)

# Compile assets
add_custom_target(assets ALL
    COMMAND ${CMAKE_COMMAND} -E remove_directory assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/assets assets
    COMMAND tools/compile_assets
    # COMMAND ${CMAKE_COMMAND} -E remove_directory assets
    DEPENDS src/tools/compile_assets
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR})

# Copy scripts
add_custom_target(scripts ALL
    COMMAND ${CMAKE_COMMAND} -E remove_directory scripts
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/scripts scripts
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
