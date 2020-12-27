set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

# cmake-format: off
set(sources
    ${CMAKE_BINARY_DIR}/version.cpp
    cli.cpp
    log.cpp
    memory.cpp
    networking/socket.cpp
    python.cpp
    system.cpp
    timer.cpp)

set(pch
    <phansar/common/pch.hpp>)

set(system_libs
    ph_vendor_cppcodec
    ph_vendor_docopt
    ph_vendor_enet
    ph_vendor_fmt
    ph_vendor_hedley
    ph_vendor_json
    ph_vendor_pybind11
    ph_vendor_rangev3
    ph_vendor_taskflow
    ph_vendor_xsimd
    Threads::Threads)
# cmake-format: on

ph_add_generic_library(ph_common "${sources}" "${pch}" "" "${system_libs}")
