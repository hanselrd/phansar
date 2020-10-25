function(ph_add_library name type)
    add_library(${name} ${type} ${ARGN})
endfunction()

function(ph_add_executable name)
    add_executable(${name} ${ARGN})
endfunction()

function(ph_target_include_directories name type)
    target_include_directories(${name} ${type} ${ARGN})
endfunction()

function(ph_target_link_libraries name type)
    target_link_libraries(${name} ${type} ${ARGN})
endfunction()

function(ph_target_link_system_libraries name type)
    set(libs ${ARGN})
    foreach(lib ${libs})
        get_target_property(lib_include_dirs ${lib} INTERFACE_INCLUDE_DIRECTORIES)
        if(lib_include_dirs)
            target_include_directories(${name} SYSTEM ${type} ${lib_include_dirs})
        endif()
        target_link_libraries(${name} ${type} ${lib})
    endforeach()
endfunction()

function(ph_target_compile_definitions name)
    target_compile_definitions(${name} PRIVATE ${ARGN})
endfunction()

function(ph_target_compile_features name)
    target_compile_features(${name} PRIVATE cxx_std_20 c_std_99)
endfunction()

function(ph_target_compile_options name)
    macro(append_compile_option testname flag)
        string(REGEX REPLACE "^-Wno-" "-W" alt ${flag})
        check_cxx_compiler_flag(${alt} PHANSAR_${testname})
        if(PHANSAR_${testname})
            target_compile_options(${name} PRIVATE ${flag})
        endif()
    endmacro()

    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        append_compile_option(HAS_OG "-Og")
        append_compile_option(HAS_G3 "-g3")
        append_compile_option(HAS_GGDB "-ggdb")
        # append_compile_option(HAS_GLLDB "-glldb")
        append_compile_option(HAS_FNO_INLINE "-fno-inline")
        append_compile_option(HAS_FSTACK_PROTECTOR_ALL "-fstack-protector-all")
        append_compile_option(HAS_OD_MSVC "/Od")
        append_compile_option(HAS_OY_MSVC "/Oy")
        append_compile_option(HAS_ZI_MSVC "/Zi")
        append_compile_option(HAS_FS_MSVC "/FS")
    else()
        append_compile_option(HAS_DFORTIFY_SOURCE_2 "-D_FORTIFY_SOURCE=2")
    endif()
    append_compile_option(HAS_WALL "-Wall")
    append_compile_option(HAS_WEXTRA "-Wextra")
    append_compile_option(HAS_WERROR "-Werror")
    append_compile_option(HAS_WPEDANTIC "-Wpedantic")
    append_compile_option(HAS_WSHADOW "-Wshadow")
    append_compile_option(HAS_WDOUBLE_PROMOTION "-Wdouble-promotion")
    append_compile_option(HAS_WFORMAT_2 "-Wformat=2")
    append_compile_option(HAS_WERROR_FORMAT_SECURITY "-Werror=format-security")
    append_compile_option(HAS_WUNDEF "-Wundef")
    append_compile_option(HAS_FNO_COMMON "-fno-common")
    append_compile_option(HAS_WCONVERSION "-Wconversion")
    append_compile_option(HAS_WFORMAT_OVERFLOW_2 "-Wformat-overflow=2")
    append_compile_option(HAS_WFORMAT_TRUNCATION_2 "-Wformat-truncation=2")
    if(ENABLE_NATIVE_OPTIMIZATIONS)
        append_compile_option(HAS_MARCH_NATIVE "-march=native")
        append_compile_option(HAS_MTUNE_NATIVE "-mtune=native")
    endif()
    append_compile_option(HAS_PIPE "-pipe")
    append_compile_option(HAS_WALL_MSVC "/Wall")
endfunction()

function(ph_add_generic_interface_library name libs system_libs)
    ph_add_library(${name} INTERFACE)

    ph_target_include_directories(${name} INTERFACE ${CMAKE_SOURCE_DIR}/include)

    if(libs)
        ph_target_link_libraries(${name} INTERFACE ${libs})
    endif()

    if(system_libs)
        ph_target_link_system_libraries(${name} INTERFACE ${system_libs})
    endif()
endfunction()

function(ph_add_generic_library name sources libs system_libs)
    ph_add_library(${name} STATIC ${sources})

    ph_target_include_directories(${name} PUBLIC ${CMAKE_SOURCE_DIR}/include)

    if(libs)
        ph_target_link_libraries(${name} PUBLIC ${libs})
    endif()

    if(system_libs)
        ph_target_link_system_libraries(${name} PUBLIC ${system_libs})
    endif()

    string(TOUPPER ${name} uppername)

    ph_target_compile_definitions(${name} BUILD_${uppername})

    ph_target_compile_features(${name})

    ph_target_compile_options(${name})
endfunction()

function(ph_add_generic_vendor_interface_library name includes libs system_libs)
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

function(ph_add_generic_vendor_library name sources includes libs system_libs)
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

    ph_target_compile_definitions(${name} BUILD_${uppername})

    ph_target_compile_features(${name})
endfunction()

function(ph_add_generic_executable name sources libs system_libs)
    ph_add_executable(${name} ${sources})

    ph_target_include_directories(${name} PRIVATE ${CMAKE_SOURCE_DIR}/include)

    if(libs)
        ph_target_link_libraries(${name} PRIVATE ${libs})
    endif()

    if(system_libs)
        ph_target_link_system_libraries(${name} PRIVATE ${system_libs})
    endif()

    string(TOUPPER ${name} uppername)

    ph_target_compile_definitions(${name} BUILD_${uppername})

    ph_target_compile_features(${name})

    ph_target_compile_options(${name})
endfunction()

function(ph_add_generic_tests name sources)
    ph_add_executable(test_${name} ${sources} ${CMAKE_SOURCE_DIR}/test/main.cpp)

    ph_target_include_directories(${name} PRIVATE ${CMAKE_SOURCE_DIR}/include)

    ph_target_link_libraries(test_${name} PRIVATE ph_vendor_catch2 ph_vendor_trompeloeil ${name})

    string(TOUPPER ${name} uppername)

    ph_target_compile_definitions(test_${name} TESTING_${uppername})

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
