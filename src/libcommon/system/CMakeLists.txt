set(sources
    ph_common_system.cpp)

set(unittest_sources
    ph_common_system.unittest.cpp)

set(libs
    ph_common_log
    ph_common_macros
    ph_vendor)

ph_add_generic_library(ph_common_system "${sources}" "${libs}")

ph_add_generic_tests(ph_common_system "${unittest_sources}")
