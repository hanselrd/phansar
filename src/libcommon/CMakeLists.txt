add_subdirectory(log)
add_subdirectory(macros)

set(libs
    ph_common_log
    ph_common_macros)

ph_add_generic_interface_library(ph_common "${libs}")
