function(ph_add_library name type)
    add_library(${name} ${type} ${ARGN})
endfunction()

function(ph_add_executable name)
    add_executable(${name} ${ARGN})
endfunction()

function(ph_target_include_directories name type)
    target_include_directories(${name} ${type} ${CMAKE_CURRENT_BINARY_DIR})
    target_include_directories(${name} ${type} ${ARGN})
endfunction()

function(ph_target_precompile_headers name type)
    if(ENABLE_CLANG_TIDY)
        target_precompile_headers(${name} PRIVATE ${ARGN})
    else()
        target_precompile_headers(${name} ${type} ${ARGN})
    endif()

    if(ENABLE_CLANG_TIDY)
        macro(check_compile_option testname flag)
            string(
                REGEX
                REPLACE "^-Wno-"
                        "-W"
                        alt
                        ${flag})
            check_cxx_compiler_flag(${alt} ${testname})
        endmacro()

        set(dummy "${CMAKE_CURRENT_BINARY_DIR}/dummy.hpp")
        file(TOUCH "${dummy}")
        check_compile_option(PHANSAR_HAS_FORCED_INCLUDE "-include ${dummy}")
        check_compile_option(PHANSAR_HAS_FORCED_INCLUDE_MSVC "/FI ${dummy}")

        set(pch "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${name}.dir/cmake_pch.hxx")
        if(PHANSAR_HAS_FORCED_INCLUDE)
            target_compile_options(${name} ${type} "SHELL:-include ${pch}")
        elseif(PHANSAR_HAS_FORCED_INCLUDE_MSVC)
            target_compile_options(${name} ${type} "SHELL:/FI ${pch}")
        endif()

        if(PHANSAR_HAS_FORCED_INCLUDE OR PHANSAR_HAS_FORCED_INCLUDE_MSVC)
            get_target_property(sources ${name} SOURCES)
            if(sources)
                set_source_files_properties(${sources} PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
            endif()
        endif()
    endif()
endfunction()

function(ph_target_link_libraries name type)
    target_link_libraries(${name} ${type} ${ARGN})
endfunction()

function(ph_target_link_system_libraries name type)
    set(libs ${ARGN})
    foreach(lib ${libs})
        if(TARGET ${lib})
            get_target_property(lib_include_dirs ${lib} INTERFACE_INCLUDE_DIRECTORIES)
            if(lib_include_dirs)
                target_include_directories(
                    ${name}
                    SYSTEM
                    ${type}
                    ${lib_include_dirs})
            endif()
        endif()
        target_link_libraries(${name} ${type} ${lib})
    endforeach()
endfunction()

function(ph_target_compile_definitions name)
    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        target_compile_definitions(${name} PRIVATE PH_BUILD_DEBUG)
    else()
        target_compile_definitions(${name} PRIVATE PH_BUILD_RELEASE)
    endif()
    if(CMAKE_SYSTEM_NAME MATCHES "Windows")
        target_compile_definitions(${name} PRIVATE PH_PLATFORM_WINDOWS NOMINMAX)
    elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
        target_compile_definitions(${name} PRIVATE PH_PLATFORM_LINUX)
    elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
        target_compile_definitions(${name} PRIVATE PH_PLATFORM_MACOS)
    endif()
    target_compile_definitions(${name} PRIVATE ${ARGN})
endfunction()

function(ph_target_compile_features name)
    target_compile_features(${name} PRIVATE cxx_std_20 c_std_99)
endfunction()

function(ph_target_compile_options name)
    macro(append_compile_option testname flag)
        string(
            REGEX
            REPLACE "^-Wno-"
                    "-W"
                    alt
                    ${flag})
        check_cxx_compiler_flag(${alt} ${testname})
        if(${testname})
            target_compile_options(${name} PRIVATE "SHELL:${flag}")
        endif()
    endmacro()

    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        append_compile_option(PHANSAR_HAS_OG "-Og")
        append_compile_option(PHANSAR_HAS_G3 "-g3")
        append_compile_option(PHANSAR_HAS_GGDB "-ggdb")
        # append_compile_option(PHANSAR_HAS_GLLDB "-glldb")
        append_compile_option(PHANSAR_HAS_FNO_INLINE "-fno-inline")
        append_compile_option(PHANSAR_HAS_FASYNCHRONOUS_UNWIND_TABLES
                              "-fasynchronous-unwind-tables")
        append_compile_option(PHANSAR_HAS_DGLIBCXX_ASSERTIONS "-D_GLIBCXX_ASSERTIONS")
        if(ENABLE_ASAN
           OR ENABLE_MSAN
           OR ENABLE_TSAN
           OR ENABLE_UBSAN)
            append_compile_option(PHANSAR_HAS_FNO_OMIT_FRAME_POINTER "-fno-omit-frame-pointer")
            if(ENABLE_ASAN)
                set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=address")
                append_compile_option(PHANSAR_HAS_FSANITIZE_ADDRESS "-fsanitize=address")
                if(PHANSAR_HAS_FSANITIZE_ADDRESS)
                    target_link_options(${name} PRIVATE "-fsanitize=address")
                endif()
            endif()
            if(ENABLE_MSAN)
                set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=memory")
                append_compile_option(PHANSAR_HAS_FSANITIZE_MEMORY "-fsanitize=memory")
                if(PHANSAR_HAS_FSANITIZE_MEMORY)
                    target_link_options(${name} PRIVATE "-fsanitize=memory")
                endif()
            endif()
            if(ENABLE_TSAN)
                set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=thread")
                append_compile_option(PHANSAR_HAS_FSANITIZE_THREAD "-fsanitize=thread")
                if(PHANSAR_HAS_FSANITIZE_THREAD)
                    target_link_options(${name} PRIVATE "-fsanitize=thread")
                endif()
            endif()
            if(ENABLE_UBSAN)
                set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=undefined")
                append_compile_option(PHANSAR_HAS_FSANITIZE_UNDEFINED "-fsanitize=undefined")
                if(PHANSAR_HAS_FSANITIZE_UNDEFINED)
                    target_link_options(${name} PRIVATE "-fsanitize=undefined")
                endif()
            endif()
            unset(CMAKE_REQUIRED_LINK_OPTIONS)
        endif()
        append_compile_option(PHANSAR_HAS_OD_MSVC "/Od")
        append_compile_option(PHANSAR_HAS_OY_MSVC "/Oy")
        append_compile_option(PHANSAR_HAS_ZI_MSVC "/Zi")
        append_compile_option(PHANSAR_HAS_FS_MSVC "/FS")
    else()
        append_compile_option(PHANSAR_HAS_DFORTIFY_SOURCE_2 "-D_FORTIFY_SOURCE=2")
    endif()
    append_compile_option(PHANSAR_HAS_WALL "-Wall")
    append_compile_option(PHANSAR_HAS_WEXTRA "-Wextra")
    append_compile_option(PHANSAR_HAS_WERROR "-Werror")
    append_compile_option(PHANSAR_HAS_WPEDANTIC "-Wpedantic")
    append_compile_option(PHANSAR_HAS_WSHADOW "-Wshadow")
    append_compile_option(PHANSAR_HAS_WDOUBLE_PROMOTION "-Wdouble-promotion")
    append_compile_option(PHANSAR_HAS_WFORMAT_2 "-Wformat=2")
    append_compile_option(PHANSAR_HAS_WERROR_FORMAT_SECURITY "-Werror=format-security")
    append_compile_option(PHANSAR_HAS_WUNDEF "-Wundef")
    append_compile_option(PHANSAR_HAS_FNO_COMMON "-fno-common")
    append_compile_option(PHANSAR_HAS_WCONVERSION "-Wconversion")
    append_compile_option(PHANSAR_HAS_WFORMAT_OVERFLOW_2 "-Wformat-overflow=2")
    append_compile_option(PHANSAR_HAS_WFORMAT_TRUNCATION_2 "-Wformat-truncation=2")
    append_compile_option(PHANSAR_HAS_WFORMAT_NONLITERAL "-Wformat-nonliteral")
    append_compile_option(PHANSAR_HAS_WPOINTER_ARITH "-Wpointer-arith")
    append_compile_option(PHANSAR_HAS_WINIT_SELF "-Winit-self")
    append_compile_option(PHANSAR_HAS_WNO_GNU_ZERO_VARIADIC_MACRO_ARGUMENTS
                          "-Wno-gnu-zero-variadic-macro-arguments")
    append_compile_option(PHANSAR_HAS_WNO_UNUSED_COMMAND_LINE_ARGUMENT
                          "-Wno-unused-command-line-argument")
    if(ENABLE_NATIVE_OPTIMIZATIONS)
        append_compile_option(PHANSAR_HAS_MARCH_NATIVE "-march=native")
        append_compile_option(PHANSAR_HAS_MTUNE_NATIVE "-mtune=native")
    endif()
    append_compile_option(PHANSAR_HAS_FSTACK_PROTECTOR_ALL "-fstack-protector-all")
    append_compile_option(PHANSAR_HAS_FSTACK_PROTECTOR_STRONG "-fstack-protector-strong")
    append_compile_option(PHANSAR_HAS_FSTACK_CLASH_PROTECTION "-fstack-clash-protection")
    append_compile_option(PHANSAR_HAS_FVISIBILITY_HIDDEN "-fvisibility=hidden")
    # append_compile_option(PHANSAR_HAS_FNO_EXCEPTIONS "-fno-exceptions")
    append_compile_option(PHANSAR_HAS_PIPE "-pipe")
    append_compile_option(PHANSAR_HAS_WALL_MSVC "/Wall")
    append_compile_option(PHANSAR_HAS_ZC_PREPROCESSOR_MSVC "/Zc:preprocessor")
endfunction()

function(
    ph_add_generic_interface_library
    name
    pch
    libs
    system_libs)
    ph_add_library(${name} INTERFACE)

    ph_target_include_directories(${name} INTERFACE ${CMAKE_SOURCE_DIR}/include)

    if(pch)
        ph_target_precompile_headers(${name} INTERFACE ${pch})
    endif()

    if(libs)
        ph_target_link_libraries(${name} INTERFACE ${libs})
    endif()

    if(system_libs)
        ph_target_link_system_libraries(${name} INTERFACE ${system_libs})
    endif()
endfunction()

function(
    ph_add_generic_library
    name
    sources
    pch
    libs
    system_libs)
    ph_add_library(${name} STATIC ${sources})

    ph_target_include_directories(${name} PUBLIC ${CMAKE_SOURCE_DIR}/include)

    if(pch)
        ph_target_precompile_headers(${name} PUBLIC ${pch})
    endif()

    if(libs)
        ph_target_link_libraries(${name} PUBLIC ${libs})
    endif()

    if(system_libs)
        ph_target_link_system_libraries(${name} PUBLIC ${system_libs})
    endif()

    string(TOUPPER ${name} uppername)

    ph_target_compile_definitions(${name} ${uppername}_BUILD)

    ph_target_compile_features(${name})

    ph_target_compile_options(${name})
endfunction()

function(
    ph_add_generic_vendor_interface_library
    name
    includes
    libs
    system_libs)
    ph_add_library(${name} INTERFACE)

    if(includes)
        ph_target_include_directories(${name} INTERFACE ${includes})
    endif()

    if(libs)
        ph_target_link_libraries(${name} INTERFACE ${libs})
    endif()

    if(system_libs)
        ph_target_link_system_libraries(${name} INTERFACE ${system_libs})
    endif()
endfunction()

function(
    ph_add_generic_vendor_library
    name
    sources
    includes
    libs
    system_libs)
    ph_add_library(${name} STATIC ${sources})

    if(includes)
        ph_target_include_directories(${name} PUBLIC ${includes})
    endif()

    if(libs)
        ph_target_link_libraries(${name} PUBLIC ${libs})
    endif()

    if(system_libs)
        ph_target_link_system_libraries(${name} PUBLIC ${system_libs})
    endif()

    string(TOUPPER ${name} uppername)

    ph_target_compile_definitions(${name} ${uppername}_BUILD)

    ph_target_compile_features(${name})
endfunction()

function(
    ph_add_generic_executable
    name
    sources
    pch
    libs
    system_libs)
    ph_add_executable(${name} ${sources})

    ph_target_include_directories(${name} PRIVATE ${CMAKE_SOURCE_DIR}/include)

    if(pch)
        ph_target_precompile_headers(${name} PRIVATE ${pch})
    endif()

    if(libs)
        ph_target_link_libraries(${name} PRIVATE ${libs})
    endif()

    if(system_libs)
        ph_target_link_system_libraries(${name} PRIVATE ${system_libs})
    endif()

    string(TOUPPER ${name} uppername)

    ph_target_compile_definitions(${name} ${uppername}_BUILD)

    ph_target_compile_features(${name})

    ph_target_compile_options(${name})
endfunction()

function(ph_add_generic_tests name sources)
    ph_add_executable(test_${name} ${sources} ${CMAKE_SOURCE_DIR}/test/main.cpp)

    ph_target_include_directories(test_${name} PRIVATE ${CMAKE_SOURCE_DIR}/include)

    ph_target_link_libraries(
        test_${name}
        PRIVATE
        ph_vendor_catch2
        ph_vendor_trompeloeil
        ${name})

    string(TOUPPER ${name} uppername)

    ph_target_compile_definitions(test_${name} ${uppername}_TESTING)

    ph_target_compile_features(test_${name})

    ph_target_compile_options(test_${name})

    catch_discover_tests(test_${name} WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endfunction()

# cmake-format: off
# target_include_directories(ph_ PRIVATE ...)
# target_compile_definitions(ph_ PRIVATE ...)
# target_compile_options(ph_ PRIVATE ...)
# target_compile_features(ph_ PRIVATE ...)
# target_sources(ph_ PRIVATE ...)
# target_precompile_headers(ph_ PRIVATE ...)
# target_link_libraries(ph_ PRIVATE ...)
# target_link_options(ph_ PRIVATE ...)
# target_link_directories(ph_ PRIVATE ...)
# cmake-format: on
