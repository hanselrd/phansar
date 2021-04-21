set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

capnp_generate_cpp(capnp_sources capnp_headers phansar.capnp)

# TODO: move to src/codegen folder
ph_add_executable(
    NAME ph_codegen
    SOURCES PRIVATE codegen.cpp
    COMPILE_FEATURES PRIVATE ${default_compile_features}
    LINK_LIBRARIES PRIVATE ph_vendor_fmt ph_vendor_llvm)

ph_add_library(
    NAME ph_common
    TYPE STATIC
    INCLUDE_DIRECTORIES PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR}
    COMPILE_DEFINITIONS PRIVATE ${default_compile_definitions}
    COMPILE_FEATURES PRIVATE ${default_compile_features}
    COMPILE_OPTIONS PRIVATE ${default_compile_options}
    SOURCES PRIVATE
            ${CMAKE_BINARY_DIR}/version.cpp
            ${capnp_sources}
            application.cpp
            bindings.cpp
            command_line.cpp
            histogram.cpp
            log.cpp
            memory.cpp
            networking/administrator_session.cpp
            networking/chat.cpp
            networking/moderator_session.cpp
            networking/root_session.cpp
            networking/service.cpp
            networking/session.cpp
            python.cpp
            timer.cpp
    LINK_LIBRARIES
        PUBLIC
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
        ph_vendor_rttr
        ph_vendor_taskflow
        ph_vendor_xsimd
        Threads::Threads
    SANITIZERS ${default_sanitizers})
