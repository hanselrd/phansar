set(unittest_sources
    common_strings_stdlib.unittest.cpp)

set(libs
    ph_common_allocators)

ph_add_generic_interface_library(ph_common_strings "${libs}" "")

ph_add_generic_tests(ph_common_strings "${unittest_sources}")
