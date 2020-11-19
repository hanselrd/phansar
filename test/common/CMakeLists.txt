# cmake-format: off
set(unittest_sources
    networking/socket.unittest.cpp
    threading/synchronized.unittest.cpp)
# cmake-format: on

ph_add_generic_tests(ph_common "${unittest_sources}")
