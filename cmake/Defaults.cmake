set(default_compile_definitions
    $<$<CONFIG:Debug>:PH_BUILD_DEBUG>
    $<$<NOT:$<CONFIG:Debug>>:PH_BUILD_RELEASE>
    $<$<PLATFORM_ID:Windows>:PH_PLATFORM_WINDOWS>
    $<$<PLATFORM_ID:Linux>:PH_PLATFORM_LINUX>
    $<$<PLATFORM_ID:Darwin>:PH_PLATFORM_MACOS>
    $<$<PLATFORM_ID:Windows>:NOMINMAX>
    $<$<CONFIG:Debug>:_GLIBCXX_ASSERTIONS>
    __STDC_CONSTANT_MACROS
    __STDC_FORMAT_MACROS
    __STDC_LIMIT_MACROS)

set(default_compile_features cxx_std_20 c_std_99)

set(default_compile_options
    $<$<CONFIG:Debug>:-Og>
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:-g3>
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:-ggdb>
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:-glldb>
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:-gsplit-dwarf>
    $<$<CONFIG:Debug>:-fno-inline>
    $<$<CONFIG:Debug>:-fasynchronous-unwind-tables>
    $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
    $<$<CONFIG:Debug>:/Od>
    $<$<CONFIG:Debug>:/Oy>
    $<$<CONFIG:Debug>:/Zi>
    $<$<CONFIG:Debug>:/FS>
    $<$<NOT:$<CONFIG:Debug>>:-D_FORTIFY_SOURCE=2>
    -Wall
    -Wextra
    -Werror
    -Wpedantic
    # -Wshadow
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
)

set(default_sanitizers
    $<$<BOOL:${ENABLE_ASAN}>:address>
    $<$<BOOL:${ENABLE_MSAN}>:memory>
    $<$<BOOL:${ENABLE_TSAN}>:thread>
    $<$<BOOL:${ENABLE_UBSAN}>:undefined>)
