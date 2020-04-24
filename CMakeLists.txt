cmake_minimum_required(VERSION 3.15...3.17 FATAL_ERROR)

project(
    phansar
    VERSION 1.0.0
    LANGUAGES CXX C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(Functions)
include(Formatters)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_program(CCACHE ccache)
if(CCACHE)
    message(STATUS "Using ccache: ${CCACHE}")
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE})
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# string(LENGTH ${CMAKE_SOURCE_DIR}/src/ SOURCE_PATH_SIZE)
# add_definitions(-D__SOURCE_PATH_SIZE__=${SOURCE_PATH_SIZE})

enable_testing()
include(CTest)

include(FetchContent)
add_subdirectory(vendor)
include(Catch)
add_subdirectory(src)
add_subdirectory(test)
