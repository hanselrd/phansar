cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(phansar VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(Functions)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
# set(THREADS_PREFER_PTHREAD_FLAG TRUE)
# find_package(Threads REQUIRED)

string(LENGTH ${CMAKE_SOURCE_DIR}/src/ SOURCE_PATH_SIZE)
add_definitions(-DPH_SOURCE_PATH_SIZE=${SOURCE_PATH_SIZE})

# enable_testing()
# include(CTest)

# add_subdirectory(vendor)
# include(Catch)
add_subdirectory(src)
