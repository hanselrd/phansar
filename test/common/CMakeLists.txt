# cmake-format: off
set(unittest_sources
    allocators/default_allocator.unittest.cpp
    containers/event_queue.unittest.cpp
    containers/stdlib.unittest.cpp
    networking/socket.unittest.cpp
    strings/stdlib.unittest.cpp
    threading/synchronized.unittest.cpp
    threading/thread_pool.unittest.cpp)
# cmake-format: on

ph_add_generic_tests(ph_common "${unittest_sources}")
