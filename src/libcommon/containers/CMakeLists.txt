set(unittest_sources
    common_containers.unittest.cpp)

set(libs
    ph_common_allocators)

ph_add_generic_interface_library(ph_common_containers "${libs}" "")

ph_add_generic_tests(ph_common_containers "${unittest_sources}")
