cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

project(
    phansar
    VERSION 1.0.0
    LANGUAGES CXX C)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed")
endif()

option(ENABLE_CMAKE_FORMAT "Enable cmake-format" OFF)
option(ENABLE_BLACK "Enable black" OFF)
option(ENABLE_CLANG_FORMAT "Enable clang-format" OFF)
option(ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
option(ENABLE_INCLUDE_WHAT_YOU_USE "Enable include-what-you-use" OFF)
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

include(CMakePrintHelpers)
include(CheckCXXCompilerFlag)
include(CheckCCompilerFlag)
include(cmake/Defaults.cmake)
include(cmake/Functions.cmake)
include(cmake/CPM.cmake)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(BUILD_SHARED_LIBS OFF)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/_vendor)

enable_testing()
include(CTest)

add_subdirectory(vendor)
include(cmake/FilePass.cmake)
include(cmake/Version.cmake)
add_subdirectory(src)
add_subdirectory(test)

unset(CMAKE_CXX_STANDARD CACHE)
unset(CMAKE_C_STANDARD CACHE)

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
set(CPACK_PACKAGE_CONTACT "Package maintainer and PGP signer")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
include(CPack)
