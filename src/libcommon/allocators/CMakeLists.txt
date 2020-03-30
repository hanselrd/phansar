set(unittest_sources
    common_allocators_default.unittest.cpp)

set(libs
    ph_common_log
    ph_common_macros
    ph_common_memory)

ph_add_generic_interface_library(ph_common_allocators "${libs}")

ph_add_generic_tests(ph_common_allocators "${unittest_sources}")
