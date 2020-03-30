set(libs
    ph_common_log
    ph_common_macros
    ph_common_memory)

ph_add_generic_interface_library(ph_common_allocators "${libs}")
