# cmake-format: off
set(unittest_sources
    codegen.unittest.cpp
    histogram.unittest.cpp
    threading/synchronized.unittest.cpp)
# cmake-format: on

ph_add_generic_tests(ph_common "${unittest_sources}")
