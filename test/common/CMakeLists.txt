ph_add_executable(
    NAME test_ph_common
    INCLUDE_DIRECTORIES PRIVATE ${CMAKE_SOURCE_DIR}/include
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
            codegen.unittest.cpp
            histogram.unittest.cpp
            threading/synchronized.unittest.cpp
            ${CMAKE_SOURCE_DIR}/test/main.cpp
    LINK_LIBRARIES
        PRIVATE
        ph_common
        ph_vendor_catch2
        ph_vendor_trompeloeil
    SANITIZERS $<$<BOOL:${ENABLE_ASAN}>:address>
               $<$<BOOL:${ENABLE_MSAN}>:memory>
               $<$<BOOL:${ENABLE_TSAN}>:thread>
               $<$<BOOL:${ENABLE_UBSAN}>:undefined>
    DISCOVER_TESTS WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
