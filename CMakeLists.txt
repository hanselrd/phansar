cmake_minimum_required(VERSION 3.16...3.17 FATAL_ERROR)

project(
    phansar
    VERSION 1.0.0
    LANGUAGES CXX C)

option(ENABLE_CMAKE_FORMAT "Enable cmake-format" OFF)
option(ENABLE_BLACK "Enable black" OFF)
option(ENABLE_CLANG_FORMAT "Enable clang-format" OFF)
option(ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
option(ENABLE_NATIVE_OPTIMIZATIONS "Enable native optimizations" OFF)
option(ENABLE_ASAN "Enable address sanitizer" OFF)
option(ENABLE_MSAN "Enable memory sanitizer" OFF)
option(ENABLE_TSAN "Enable thread sanitizer" OFF)
option(ENABLE_UBSAN "Enable undefined behavior sanitizer" OFF)

if(NOT WIN32)
    find_program(CCACHE_EXECUTABLE ccache)
    if(CCACHE_EXECUTABLE)
        message(STATUS "Using ccache: ${CCACHE_EXECUTABLE}")
        set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_EXECUTABLE})
        set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_EXECUTABLE})
    endif()
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(CheckCXXCompilerFlag)
include(CheckCCompilerFlag)
include(Functions)
include(Formatters)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release)
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
include(Version)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(assets)

set(CPACK_GENERATOR "TGZ")
set(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR "Phansar")
set(CPACK_PACKAGE_DESCRIPTION "Game written using a modern C++ stack")
string(TOLOWER ${CMAKE_BUILD_TYPE} CPACK_BUILD_TYPE)
string(TOLOWER ${CMAKE_SYSTEM_NAME} CPACK_SYSTEM_NAME)
set(CPACK_PACKAGE_FILE_NAME
    "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}.${GIT_SHORT_HASH}.${CPACK_BUILD_TYPE}-${CPACK_SYSTEM_NAME}"
)
set(CPACK_PACKAGE_CHECKSUM "SHA1")
set(CPACK_PACKAGE_CONTACT "Hansel De La Cruz")
include(CPack)
