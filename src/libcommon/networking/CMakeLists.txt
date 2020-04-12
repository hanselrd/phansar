# cmake-format: off
set(sources
    common_networking_socket.cpp)

set(unittest_sources
    common_networking_socket.unittest.cpp)

set(libs
    ph_common_containers
    ph_common_log
    ph_vendor_plibsys)
# cmake-format: on

ph_add_generic_library(ph_common_networking "${sources}" "${libs}" "")

ph_add_generic_tests(ph_common_networking "${unittest_sources}")
