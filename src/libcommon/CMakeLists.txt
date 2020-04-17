add_subdirectory(allocators)
add_subdirectory(config)
add_subdirectory(containers)
add_subdirectory(log)
add_subdirectory(macros)
add_subdirectory(memory)
add_subdirectory(networking)
add_subdirectory(strings)
add_subdirectory(system)
add_subdirectory(threading)

# cmake-format: off
set(libs
    ph_common_allocators
    ph_common_config
    ph_common_containers
    ph_common_log
    ph_common_macros
    ph_common_memory
    ph_common_networking
    ph_common_strings
    ph_common_system
    ph_common_threading)
# cmake-format: on

ph_add_generic_interface_library(ph_common "${libs}" "")
