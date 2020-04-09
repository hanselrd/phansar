set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

# cmake-format: off
set(sources
    common_threading_thread_pool.cpp)

set(unittest_sources
    common_threading_synchronized.unittest.cpp
    common_threading_thread_pool.unittest.cpp)

set(libs
    ph_common_containers
    ph_common_log)

set(system_libs
    Threads::Threads)
# cmake-format: on

ph_add_generic_library(ph_common_threading "${sources}" "${libs}" "${system_libs}")

ph_add_generic_tests(ph_common_threading "${unittest_sources}")
