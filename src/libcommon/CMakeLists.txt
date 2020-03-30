add_subdirectory(allocators)
add_subdirectory(log)
add_subdirectory(macros)
add_subdirectory(memory)
add_subdirectory(system)

set(libs
    ph_common_allocators
    ph_common_log
    ph_common_macros
    ph_common_memory
    ph_common_system)

ph_add_generic_interface_library(ph_common "${libs}")
