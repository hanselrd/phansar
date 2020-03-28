set(sources
    ph_common_log.cpp)

set(unittest_sources
    ph_common_log.unittest.cpp)

set(libs
    ph_vendor)

ph_add_generic_library(ph_common_log "${sources}" "${libs}")

ph_add_generic_tests(ph_common_log "${unittest_sources}")
