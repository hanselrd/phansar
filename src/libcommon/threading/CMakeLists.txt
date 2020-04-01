set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

set(unittest_sources
    common_threading_synchronized.unittest.cpp)

set(libs
    ph_common_log
    Threads::Threads)

ph_add_generic_interface_library(ph_common_threading "${libs}")

ph_add_generic_tests(ph_common_threading "${unittest_sources}")
