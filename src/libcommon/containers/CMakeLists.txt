# cmake-format: off
set(unittest_sources
    common_containers_event_queue.unittest.cpp
    common_containers_stdlib.unittest.cpp)

set(libs
    ph_common_allocators)
# cmake-format: on

ph_add_generic_interface_library(ph_common_containers "${libs}" "")

ph_add_generic_tests(ph_common_containers "${unittest_sources}")
