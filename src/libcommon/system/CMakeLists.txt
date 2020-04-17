# cmake-format: off
set(sources
    common_system.cpp)

set(libs
    ph_common_config
    ph_common_log
    ph_common_macros
    ph_common_memory
    ph_vendor_plibsys)
# cmake-format: on

ph_add_generic_library(ph_common_system "${sources}" "${libs}" "")
