set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

capnp_generate_cpp(capnp_sources capnp_headers phansar.capnp)

# cmake-format: off
set(sources
    ${CMAKE_BINARY_DIR}/version.cpp
    ${capnp_sources}
    application.cpp
    command_line.cpp
    log.cpp
    memory.cpp
    networking/service.cpp
    networking/session.cpp
    networking/socket.cpp
    python.cpp
    timer.cpp)

set(pch
    <phansar/common/pch.hpp>)

set(system_libs
    ph_vendor_capnproto
    ph_vendor_cppcodec
    ph_vendor_cxxopts
    ph_vendor_entt
    ph_vendor_fmt
    ph_vendor_hedley
    ph_vendor_json
    ph_vendor_kangaru
    ph_vendor_pybind11
    ph_vendor_rangev3
    ph_vendor_taskflow
    ph_vendor_xsimd
    Threads::Threads)
# cmake-format: on

ph_add_generic_library(
    ph_common
    "${sources}"
    "${pch}"
    ""
    "${system_libs}")
