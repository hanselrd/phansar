# cmake-format: off
set(unittest_sources
    allocators/mallocator.unittest.cpp
    networking/socket.unittest.cpp
    threading/synchronized.unittest.cpp
    threading/thread_pool.unittest.cpp
    timer.unittest.cpp)
# cmake-format: on

ph_add_generic_tests(ph_common "${unittest_sources}")
