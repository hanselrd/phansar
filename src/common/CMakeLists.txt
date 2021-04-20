set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

capnp_generate_cpp(capnp_sources capnp_headers phansar.capnp)

# TODO: move to src/codegen folder
ph_add_executable(
    NAME ph_codegen
    SOURCES PRIVATE codegen.cpp
    COMPILE_FEATURES PRIVATE cxx_std_20 c_std_99
    LINK_LIBRARIES PRIVATE ph_vendor_fmt ph_vendor_llvm)

ph_add_library(
    NAME ph_common
    TYPE STATIC
    INCLUDE_DIRECTORIES PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR}
    COMPILE_DEFINITIONS
        PRIVATE
        $<$<CONFIG:Debug>:PH_BUILD_DEBUG>
        $<$<NOT:$<CONFIG:Debug>>:PH_BUILD_RELEASE>
        $<$<PLATFORM_ID:Windows>:PH_PLATFORM_WINDOWS>
        $<$<PLATFORM_ID:Windows>:NOMINMAX>
        $<$<PLATFORM_ID:Linux>:PH_PLATFORM_LINUX>
        $<$<PLATFORM_ID:Darwin>:PH_PLATFORM_MACOS>
    COMPILE_FEATURES PRIVATE cxx_std_20 c_std_99
    COMPILE_OPTIONS
        PRIVATE
        $<$<CONFIG:Debug>:-Og>
        $<$<CONFIG:Debug>:-g3>
        $<$<CONFIG:Debug>:-ggdb>
        # $<$<CONFIG:Debug>:-glldb>
        $<$<CONFIG:Debug>:-fno-inline>
        $<$<CONFIG:Debug>:-fasynchronous-unwind-tables>
        $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
        $<$<CONFIG:Debug>:-D_GLIBCXX_ASSERTIONS>
        $<$<CONFIG:Debug>:/Od>
        $<$<CONFIG:Debug>:/Oy>
        $<$<CONFIG:Debug>:/Z7>
        $<$<CONFIG:Debug>:/FS>
        $<$<NOT:$<CONFIG:Debug>>:-D_FORTIFY_SOURCE=2>
        -Wall
        -Wextra
        # -Werror
        -Wpedantic
        -Wshadow
        -Wdouble-promotion
        -Wformat=2
        -Werror=format-security
        -Wundef
        -Wno-defaulted-function-deleted
        -fno-common
        -Wconversion
        -Wformat-overflow=2
        -Wformat-truncation=2
        -Wformat-nonliteral
        -Wpointer-arith
        -Wthread-safety
        -Winit-self
        -Wno-gnu-zero-variadic-macro-arguments
        -Wno-unused-command-line-argument
        $<$<BOOL:${ENABLE_NATIVE_OPTIMIZATIONS}>:-march=native>
        $<$<BOOL:${ENABLE_NATIVE_OPTIMIZATIONS}>:-mtune=native>
        -fstack-protector-all
        -fstack-protector-strong
        -fstack-clash-protection
        -fvisibility=hidden
        -fvisibility-inlines-hidden
        -fdiagnostics-color
        -pipe
        /Wall
        # /Zc:preprocessor
    SOURCES PRIVATE
            ${CMAKE_BINARY_DIR}/version.cpp
            # ${capnp_sources}
            application.cpp
            bindings.cpp
            command_line.cpp
            histogram.cpp
            log.cpp
            memory.cpp
            # networking/administrator_session.cpp networking/chat.cpp
            # networking/moderator_session.cpp networking/root_session.cpp networking/service.cpp
            # networking/session.cpp
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
    SANITIZERS $<$<BOOL:${ENABLE_ASAN}>:address>
               $<$<BOOL:${ENABLE_MSAN}>:memory>
               $<$<BOOL:${ENABLE_TSAN}>:thread>
               $<$<BOOL:${ENABLE_UBSAN}>:undefined>)
