set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

set(CAPNPC_OUTPUT_DIR ${CMAKE_BINARY_DIR}/capnp/phansar/common)
capnp_generate_cpp(
    capnp_sources
    capnp_headers
    schema/asset.capnp
    schema/channel.capnp
    schema/chat.capnp
    schema/datetime.capnp
    schema/id.capnp
    schema/packet.capnp
    schema/pointer.cog.capnp
    schema/publish.capnp
    schema/result.capnp
    schema/transaction_chain.cog.capnp
    schema/transaction.capnp
    schema/user.capnp
    schema/vector.capnp
    schema/world.capnp)

ph_add_library(
    NAME ph_common
    TYPE STATIC
    INCLUDE_DIRECTORIES PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/capnp
    COMPILE_DEFINITIONS PRIVATE ${default_compile_definitions}
    COMPILE_FEATURES PRIVATE ${default_compile_features}
    COMPILE_OPTIONS PRIVATE ${default_compile_options}
    SOURCES PRIVATE
            ${CMAKE_BINARY_DIR}/version.cpp
            ${capnp_sources}
            errc.cog.cpp
            error.cog.cpp
            logger.cpp
            network/socket.cpp
            reflect/debug_visitor.cpp
            reflect/json_serializer.cpp
            reflect/pybind_visitor.cpp
            service_container.cpp
    LINK_LIBRARIES
        PUBLIC
        ph_vendor_capnproto
        ph_vendor_cppcodec
        ph_vendor_cxxopts
        ph_vendor_enet
        ph_vendor_entt
        ph_vendor_fmt
        ph_vendor_hedley
        ph_vendor_json
        ph_vendor_kangaru
        ph_vendor_pybind11
        ph_vendor_rangev3
        ph_vendor_rttr
        ph_vendor_sigslot
        ph_vendor_sol2
        ph_vendor_spdlog
        ph_vendor_taskflow
        ph_vendor_xsimd
        Threads::Threads
    SANITIZERS ${default_sanitizers}
    DEPENDENCIES codegen)
