cmake_minimum_required(VERSION 3.15...3.17 FATAL_ERROR)

project(
    phansar
    VERSION 1.0.0
    LANGUAGES CXX C)

option(ENABLE_CMAKE_FORMAT "Enable cmake-format" OFF)
option(ENABLE_BLACK "Enable black" OFF)
option(ENABLE_CLANG_FORMAT "Enable clang-format" OFF)
option(ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
option(ENABLE_NATIVE_OPTIMIZATIONS "Enable native optimizations" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(CheckCXXCompilerFlag)
include(CheckCCompilerFlag)
include(Functions)
include(Formatters)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_program(CCACHE_EXECUTABLE ccache)
if(CCACHE_EXECUTABLE)
    message(STATUS "Using ccache: ${CCACHE_EXECUTABLE}")
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_EXECUTABLE})
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_EXECUTABLE})
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

enable_testing()
include(CTest)

include(FetchContent)
add_subdirectory(vendor)
include(Catch)
add_subdirectory(src)
add_subdirectory(test)
