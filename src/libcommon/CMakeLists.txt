# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/common)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/common)

add_subdirectory(log)

set(libs
    ph_common_log)

ph_add_generic_interface_library(ph_common "${libs}")
