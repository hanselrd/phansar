function(__target_compile_options target)
    set(args)

    foreach(arg IN LISTS ARGN)
        if(NOT
           (arg STREQUAL "BEFORE"
            OR arg STREQUAL "INTERFACE"
            OR arg STREQUAL "PUBLIC"
            OR arg STREQUAL "PRIVATE"))
            string(MAKE_C_IDENTIFIER ${arg} identifier)
            string(TOUPPER ${identifier} identifier)
            string(SHA1 hash ${arg})

            if(${arg} MATCHES "[-/][a-zA-Z0-9=:_-]+")
                string(
                    REGEX
                    REPLACE "^-Wno-"
                            "-W"
                            alt
                            ${CMAKE_MATCH_0})
                check_cxx_compiler_flag(${alt} PHANSAR_HAS_${identifier}_${hash})

                if(PHANSAR_HAS_${identifier}_${hash})
                    list(APPEND args "SHELL:${arg}")
                endif()
            endif()
        else()
            list(APPEND args ${arg})
        endif()
    endforeach()

    target_compile_options(${target} ${args})
endfunction()

function(__target_link_libraries target)
    function(__get_link_libraries target outputs)
        set(_outputs)
        list(APPEND visited ${target})
        get_target_property(interface_link_libs ${target} INTERFACE_LINK_LIBRARIES)
        get_target_property(type ${target} TYPE)
        if(type STREQUAL "INTERFACE_LIBRARY")
            get_target_property(link_libs ${target} LINK_LIBRARIES)
        endif()
        foreach(link_lib IN LISTS interface_link_libs link_libs)
            if(TARGET ${link_lib})
                list(
                    FIND
                    visited
                    ${link_lib}
                    result)
                if(result EQUAL -1)
                    __get_link_libraries(${link_lib} __outputs)
                    list(
                        APPEND
                        _outputs
                        ${link_lib}
                        ${__outputs})
                endif()
            endif()
        endforeach()

        set(visited
            ${visited}
            PARENT_SCOPE)
        set(${outputs}
            ${_outputs}
            PARENT_SCOPE)
    endfunction()

    set(args)
    list(
        GET
        ARGN
        0
        arg0)

    if(arg0 STREQUAL "SYSTEM")
        set(system ON)
    else()
        set(system OFF)
    endif()

    foreach(arg IN LISTS ARGN)
        if(arg STREQUAL "SYSTEM")
            continue()
        endif()

        if(NOT
           (arg STREQUAL "INTERFACE"
            OR arg STREQUAL "PUBLIC"
            OR arg STREQUAL "PRIVATE"))
            if(TARGET ${arg})
                if(system)
                    __get_link_libraries(${arg} outputs)
                    foreach(output IN LISTS outputs)
                        get_target_property(interface_include_dirs ${output}
                                            INTERFACE_INCLUDE_DIRECTORIES)
                        if(interface_include_dirs)
                            target_include_directories(${target} SYSTEM
                                                       INTERFACE ${interface_include_dirs})
                        endif()
                    endforeach()
                    get_target_property(interface_include_dirs ${arg} INTERFACE_INCLUDE_DIRECTORIES)
                    if(interface_include_dirs)
                        target_include_directories(${target} SYSTEM
                                                   INTERFACE ${interface_include_dirs})
                    endif()
                endif()
            endif()
            list(APPEND args ${arg})
        else()
            list(APPEND args ${arg})
        endif()
    endforeach()

    target_link_libraries(${target} ${args})
endfunction()

function(ph_add_library)
    cmake_parse_arguments(
        ARG
        ""
        "NAME;TYPE"
        "INCLUDE_DIRECTORIES;COMPILE_DEFINITIONS;COMPILE_FEATURES;COMPILE_OPTIONS;PRECOMPILE_HEADERS;SOURCES;LINK_LIBRARIES;LINK_OPTIONS;LINK_DIRECTORIES;DEPENDENCIES;INSTALL"
        ${ARGN})

    if(ARG_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "called with unrecognized parameters: ${ARG_UNPARSED_ARGUMENTS}")
    endif()

    add_library(${ARG_NAME} ${ARG_TYPE})

    if(ARG_INCLUDE_DIRECTORIES)
        target_include_directories(${ARG_NAME} ${ARG_INCLUDE_DIRECTORIES})
    endif()

    if(ARG_COMPILE_DEFINITIONS)
        target_compile_definitions(${ARG_NAME} ${ARG_COMPILE_DEFINITIONS})
    endif()

    if(ARG_COMPILE_FEATURES)
        target_compile_features(${ARG_NAME} ${ARG_COMPILE_FEATURES})
    endif()

    if(ARG_COMPILE_OPTIONS)
        __target_compile_options(${ARG_NAME} ${ARG_COMPILE_OPTIONS})
    endif()

    if(ARG_PRECOMPILE_HEADERS)
        target_precompile_headers(${ARG_NAME} ${ARG_PRECOMPILE_HEADERS})
    endif()

    if(ARG_SOURCES)
        target_sources(${ARG_NAME} ${ARG_SOURCES})
    endif()

    if(ARG_LINK_LIBRARIES)
        __target_link_libraries(${ARG_NAME} ${ARG_LINK_LIBRARIES})
    endif()

    if(ARG_LINK_OPTIONS)
        target_link_options(${ARG_NAME} ${ARG_LINK_OPTIONS})
    endif()

    if(ARG_LINK_DIRECTORIES)
        target_link_directories(${ARG_NAME} ${ARG_LINK_DIRECTORIES})
    endif()

    if(ARG_DEPENDENCIES)
        add_dependencies(${ARG_NAME} ${ARG_DEPENDENCIES})
    endif()

    if(ARG_INSTALL)
        install(TARGETS ${ARG_NAME} ${ARG_INSTALL})
    endif()
endfunction()

function(ph_add_executable)
    cmake_parse_arguments(
        ARG
        ""
        "NAME"
        "INCLUDE_DIRECTORIES;COMPILE_DEFINITIONS;COMPILE_FEATURES;COMPILE_OPTIONS;PRECOMPILE_HEADERS;SOURCES;LINK_LIBRARIES;LINK_OPTIONS;LINK_DIRECTORIES;DEPENDENCIES;INSTALL;DISCOVER_TESTS"
        ${ARGN})

    if(ARG_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "called with unrecognized parameters: ${ARG_UNPARSED_ARGUMENTS}")
    endif()

    add_executable(${ARG_NAME})

    if(ARG_INCLUDE_DIRECTORIES)
        target_include_directories(${ARG_NAME} ${ARG_INCLUDE_DIRECTORIES})
    endif()

    if(ARG_COMPILE_DEFINITIONS)
        target_compile_definitions(${ARG_NAME} ${ARG_COMPILE_DEFINITIONS})
    endif()

    if(ARG_COMPILE_FEATURES)
        target_compile_features(${ARG_NAME} ${ARG_COMPILE_FEATURES})
    endif()

    if(ARG_COMPILE_OPTIONS)
        __target_compile_options(${ARG_NAME} ${ARG_COMPILE_OPTIONS})
    endif()

    if(ARG_PRECOMPILE_HEADERS)
        target_precompile_headers(${ARG_NAME} ${ARG_PRECOMPILE_HEADERS})
    endif()

    if(ARG_SOURCES)
        target_sources(${ARG_NAME} ${ARG_SOURCES})
    endif()

    if(ARG_LINK_LIBRARIES)
        __target_link_libraries(${ARG_NAME} ${ARG_LINK_LIBRARIES})
    endif()

    if(ARG_LINK_OPTIONS)
        target_link_options(${ARG_NAME} ${ARG_LINK_OPTIONS})
    endif()

    if(ARG_LINK_DIRECTORIES)
        target_link_directories(${ARG_NAME} ${ARG_LINK_DIRECTORIES})
    endif()

    if(ARG_DEPENDENCIES)
        add_dependencies(${ARG_NAME} ${ARG_DEPENDENCIES})
    endif()

    if(ARG_INSTALL)
        install(TARGETS ${ARG_NAME} ${ARG_INSTALL})
    endif()

    if(ARG_DISCOVER_TESTS)
        catch_discover_tests(${ARG_NAME} ${ARG_DISCOVER_TESTS})
    endif()
endfunction()

# cmake-format: off
# ph_add_library(
#     NAME ph_test_lib
#     TYPE STATIC
#     INCLUDE_DIRECTORIES PUBLIC ${CMAKE_SOURCE_DIR}/include
#     COMPILE_DEFINITIONS PRIVATE defines
#     COMPILE_FEATURES PRIVATE cxx_std_20 c_std_99
#     COMPILE_OPTIONS PRIVATE options
#     PRECOMPILE_HEADERS PRIVATE pchs
#     SOURCES PRIVATE ${CMAKE_SOURCE_DIR}/src/common/codegen.cpp
#     LINK_LIBRARIES PRIVATE libs
#     LINK_OPTIONS PRIVATE options
#     LINK_DIRECTORIES PRIVATE directories)

# ph_add_executable(
#     NAME ph_test_exe
#     INCLUDE_DIRECTORIES PUBLIC ${CMAKE_SOURCE_DIR}/include
#     COMPILE_DEFINITIONS PRIVATE defines
#     COMPILE_FEATURES PRIVATE cxx_std_20 c_std_99
#     COMPILE_OPTIONS PRIVATE options
#     PRECOMPILE_HEADERS PRIVATE pchs
#     SOURCES PRIVATE ${CMAKE_SOURCE_DIR}/src/common/codegen.cpp
#     LINK_LIBRARIES PRIVATE libs
#     LINK_OPTIONS PRIVATE options
#     LINK_DIRECTORIES PRIVATE directories)
# cmake-format: on

# cmake-format: off
# function(ph_add_library name type)
#     add_library(${name} ${type} ${ARGN})
# endfunction()

# function(ph_add_executable name)
#     add_executable(${name} ${ARGN})
# endfunction()

# function(ph_target_include_directories name type)
#     target_include_directories(${name} ${type} ${CMAKE_CURRENT_BINARY_DIR})
#     target_include_directories(${name} ${type} ${ARGN})
# endfunction()

# function(ph_target_precompile_headers name type)
#     if(ENABLE_CLANG_TIDY)
#         target_precompile_headers(${name} PRIVATE ${ARGN})
#     else()
#         target_precompile_headers(${name} ${type} ${ARGN})
#     endif()

#     if(ENABLE_CLANG_TIDY)
#         macro(check_compile_option testname flag)
#             string(
#                 REGEX
#                 REPLACE "^-Wno-"
#                         "-W"
#                         alt
#                         ${flag})
#             check_cxx_compiler_flag(${alt} ${testname})
#         endmacro()

#         set(dummy "${CMAKE_CURRENT_BINARY_DIR}/dummy.hpp")
#         file(TOUCH "${dummy}")
#         check_compile_option(PHANSAR_HAS_FORCED_INCLUDE "-include ${dummy}")
#         check_compile_option(PHANSAR_HAS_FORCED_INCLUDE_MSVC "/FI ${dummy}")

#         set(pch "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${name}.dir/cmake_pch.hxx")
#         if(PHANSAR_HAS_FORCED_INCLUDE)
#             target_compile_options(${name} ${type} "SHELL:-include ${pch}")
#         elseif(PHANSAR_HAS_FORCED_INCLUDE_MSVC)
#             target_compile_options(${name} ${type} "SHELL:/FI ${pch}")
#         endif()

#         if(PHANSAR_HAS_FORCED_INCLUDE OR PHANSAR_HAS_FORCED_INCLUDE_MSVC)
#             get_target_property(sources ${name} SOURCES)
#             if(sources)
#                 set_source_files_properties(${sources} PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
#             endif()
#         endif()
#     endif()
# endfunction()

# function(ph_target_link_libraries name type)
#     target_link_libraries(${name} ${type} ${ARGN})
# endfunction()

# function(ph_target_link_system_libraries name type)
#     function(get_link_libraries output_list target)
#         get_target_property(imported ${target} IMPORTED)
#         list(APPEND visited_targets ${target})
#         if(imported)
#             get_target_property(libs ${target} INTERFACE_LINK_LIBRARIES)
#         else()
#             get_target_property(libs ${target} LINK_LIBRARIES)
#         endif()
#         set(lib_files "")
#         foreach(lib ${libs})
#             if(TARGET ${lib})
#                 list(
#                     FIND
#                     visited_targets
#                     ${lib}
#                     visited)
#                 if(${visited} EQUAL -1)
#                     get_link_libraries(link_lib_files ${lib})
#                     list(
#                         APPEND
#                         lib_files
#                         ${lib}
#                         ${link_lib_files})
#                 endif()
#             endif()
#         endforeach()
#         set(visited_targets
#             ${visited_targets}
#             PARENT_SCOPE)
#         set(${output_list}
#             ${lib_files}
#             PARENT_SCOPE)
#     endfunction()

#     set(libs ${ARGN})
#     foreach(lib ${libs})
#         if(TARGET ${lib})
#             get_link_libraries(lib_targets ${lib})
#             foreach(lib_target ${lib_targets})
#                 get_target_property(lib_include_dirs ${lib_target} INTERFACE_INCLUDE_DIRECTORIES)
#                 if(lib_include_dirs)
#                     target_include_directories(
#                         ${name}
#                         SYSTEM
#                         ${type}
#                         ${lib_include_dirs})
#                 endif()
#             endforeach()
#             get_target_property(lib_include_dirs ${lib} INTERFACE_INCLUDE_DIRECTORIES)
#             if(lib_include_dirs)
#                 target_include_directories(
#                     ${name}
#                     SYSTEM
#                     ${type}
#                     ${lib_include_dirs})
#             endif()
#         endif()
#         target_link_libraries(${name} ${type} ${lib})
#     endforeach()
# endfunction()

# function(ph_target_compile_definitions name)
#     if(CMAKE_BUILD_TYPE MATCHES "Debug")
#         target_compile_definitions(${name} PRIVATE PH_BUILD_DEBUG)
#     else()
#         target_compile_definitions(${name} PRIVATE PH_BUILD_RELEASE)
#     endif()
#     if(CMAKE_SYSTEM_NAME MATCHES "Windows")
#         target_compile_definitions(${name} PRIVATE PH_PLATFORM_WINDOWS NOMINMAX)
#     elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
#         target_compile_definitions(${name} PRIVATE PH_PLATFORM_LINUX)
#     elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
#         target_compile_definitions(${name} PRIVATE PH_PLATFORM_MACOS)
#     endif()
#     target_compile_definitions(${name} PRIVATE ${ARGN})
# endfunction()

# function(ph_target_compile_features name)
#     target_compile_features(${name} PRIVATE cxx_std_20 c_std_99)
# endfunction()

# function(ph_target_compile_options name)
#     macro(append_compile_option testname flag)
#         string(
#             REGEX
#             REPLACE "^-Wno-"
#                     "-W"
#                     alt
#                     ${flag})
#         check_cxx_compiler_flag(${alt} ${testname})
#         if(${testname})
#             target_compile_options(${name} PRIVATE "SHELL:${flag}")
#         endif()
#     endmacro()

#     if(CMAKE_BUILD_TYPE MATCHES "Debug")
#         append_compile_option(PHANSAR_HAS_OG "-Og")
#         append_compile_option(PHANSAR_HAS_G3 "-g3")
#         append_compile_option(PHANSAR_HAS_GGDB "-ggdb")
#         # append_compile_option(PHANSAR_HAS_GLLDB "-glldb")
#         append_compile_option(PHANSAR_HAS_FNO_INLINE "-fno-inline")
#         append_compile_option(PHANSAR_HAS_FASYNCHRONOUS_UNWIND_TABLES
#                               "-fasynchronous-unwind-tables")
#         append_compile_option(PHANSAR_HAS_DGLIBCXX_ASSERTIONS "-D_GLIBCXX_ASSERTIONS")
#         if(ENABLE_ASAN
#            OR ENABLE_MSAN
#            OR ENABLE_TSAN
#            OR ENABLE_UBSAN)
#             append_compile_option(PHANSAR_HAS_FNO_OMIT_FRAME_POINTER "-fno-omit-frame-pointer")
#             if(ENABLE_ASAN)
#                 set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=address")
#                 append_compile_option(PHANSAR_HAS_FSANITIZE_ADDRESS "-fsanitize=address")
#                 if(PHANSAR_HAS_FSANITIZE_ADDRESS)
#                     target_link_options(${name} PRIVATE "-fsanitize=address")
#                 endif()
#             endif()
#             if(ENABLE_MSAN)
#                 set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=memory")
#                 append_compile_option(PHANSAR_HAS_FSANITIZE_MEMORY "-fsanitize=memory")
#                 if(PHANSAR_HAS_FSANITIZE_MEMORY)
#                     target_link_options(${name} PRIVATE "-fsanitize=memory")
#                 endif()
#             endif()
#             if(ENABLE_TSAN)
#                 set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=thread")
#                 append_compile_option(PHANSAR_HAS_FSANITIZE_THREAD "-fsanitize=thread")
#                 if(PHANSAR_HAS_FSANITIZE_THREAD)
#                     target_link_options(${name} PRIVATE "-fsanitize=thread")
#                 endif()
#             endif()
#             if(ENABLE_UBSAN)
#                 set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=undefined")
#                 append_compile_option(PHANSAR_HAS_FSANITIZE_UNDEFINED "-fsanitize=undefined")
#                 if(PHANSAR_HAS_FSANITIZE_UNDEFINED)
#                     target_link_options(${name} PRIVATE "-fsanitize=undefined")
#                 endif()
#             endif()
#             unset(CMAKE_REQUIRED_LINK_OPTIONS)
#         endif()
#         append_compile_option(PHANSAR_HAS_OD_MSVC "/Od")
#         append_compile_option(PHANSAR_HAS_OY_MSVC "/Oy")
#         append_compile_option(PHANSAR_HAS_ZI_MSVC "/Zi")
#         append_compile_option(PHANSAR_HAS_FS_MSVC "/FS")
#     else()
#         append_compile_option(PHANSAR_HAS_DFORTIFY_SOURCE_2 "-D_FORTIFY_SOURCE=2")
#     endif()
#     append_compile_option(PHANSAR_HAS_WALL "-Wall")
#     append_compile_option(PHANSAR_HAS_WEXTRA "-Wextra")
#     append_compile_option(PHANSAR_HAS_WERROR "-Werror")
#     append_compile_option(PHANSAR_HAS_WPEDANTIC "-Wpedantic")
#     append_compile_option(PHANSAR_HAS_WSHADOW "-Wshadow")
#     append_compile_option(PHANSAR_HAS_WDOUBLE_PROMOTION "-Wdouble-promotion")
#     append_compile_option(PHANSAR_HAS_WFORMAT_2 "-Wformat=2")
#     append_compile_option(PHANSAR_HAS_WERROR_FORMAT_SECURITY "-Werror=format-security")
#     # append_compile_option(PHANSAR_HAS_WUNDEF "-Wundef")
#     append_compile_option(PHANSAR_HAS_WNO_DEFAULTED_FUNCTION_DELETED
#                           "-Wno-defaulted-function-deleted")
#     append_compile_option(PHANSAR_HAS_FPCH_PREPROCESS "-fpch-preprocess")
#     append_compile_option(PHANSAR_HAS_FNO_COMMON "-fno-common")
#     append_compile_option(PHANSAR_HAS_WCONVERSION "-Wconversion")
#     append_compile_option(PHANSAR_HAS_WFORMAT_OVERFLOW_2 "-Wformat-overflow=2")
#     append_compile_option(PHANSAR_HAS_WFORMAT_TRUNCATION_2 "-Wformat-truncation=2")
#     append_compile_option(PHANSAR_HAS_WFORMAT_NONLITERAL "-Wformat-nonliteral")
#     append_compile_option(PHANSAR_HAS_WPOINTER_ARITH "-Wpointer-arith")
#     append_compile_option(PHANSAR_HAS_WINIT_SELF "-Winit-self")
#     append_compile_option(PHANSAR_HAS_WNO_GNU_ZERO_VARIADIC_MACRO_ARGUMENTS
#                           "-Wno-gnu-zero-variadic-macro-arguments")
#     append_compile_option(PHANSAR_HAS_WNO_UNUSED_COMMAND_LINE_ARGUMENT
#                           "-Wno-unused-command-line-argument")
#     if(ENABLE_NATIVE_OPTIMIZATIONS)
#         append_compile_option(PHANSAR_HAS_MARCH_NATIVE "-march=native")
#         append_compile_option(PHANSAR_HAS_MTUNE_NATIVE "-mtune=native")
#     endif()
#     append_compile_option(PHANSAR_HAS_FSTACK_PROTECTOR_ALL "-fstack-protector-all")
#     append_compile_option(PHANSAR_HAS_FSTACK_PROTECTOR_STRONG "-fstack-protector-strong")
#     append_compile_option(PHANSAR_HAS_FSTACK_CLASH_PROTECTION "-fstack-clash-protection")
#     append_compile_option(PHANSAR_HAS_FVISIBILITY_HIDDEN "-fvisibility=hidden")
#     append_compile_option(PHANSAR_HAS_FVISIBILITY_INLINES_HIDDEN "-fvisibility-inlines-hidden")
#     # append_compile_option(PHANSAR_HAS_FNO_EXCEPTIONS "-fno-exceptions")
#     append_compile_option(PHANSAR_HAS_PIPE "-pipe")
#     append_compile_option(PHANSAR_HAS_WALL_MSVC "/Wall")
#     append_compile_option(PHANSAR_HAS_ZC_PREPROCESSOR_MSVC "/Zc:preprocessor")
# endfunction()

# function(
#     ph_add_generic_interface_library
#     name
#     pch
#     libs
#     system_libs)
#     ph_add_library(${name} INTERFACE)

#     ph_target_include_directories(${name} INTERFACE ${CMAKE_SOURCE_DIR}/include)

#     if(pch)
#         ph_target_precompile_headers(${name} INTERFACE ${pch})
#     endif()

#     if(libs)
#         ph_target_link_libraries(${name} INTERFACE ${libs})
#     endif()

#     if(system_libs)
#         ph_target_link_system_libraries(${name} INTERFACE ${system_libs})
#     endif()
# endfunction()

# function(
#     ph_add_generic_library
#     name
#     sources
#     pch
#     libs
#     system_libs)
#     ph_add_library(${name} STATIC ${sources})

#     ph_target_include_directories(${name} PUBLIC ${CMAKE_SOURCE_DIR}/include)

#     if(pch)
#         ph_target_precompile_headers(${name} PUBLIC ${pch})
#     endif()

#     if(libs)
#         ph_target_link_libraries(${name} PUBLIC ${libs})
#     endif()

#     if(system_libs)
#         ph_target_link_system_libraries(${name} PUBLIC ${system_libs})
#     endif()

#     string(TOUPPER ${name} uppername)

#     ph_target_compile_definitions(${name} ${uppername}_BUILD)

#     ph_target_compile_features(${name})

#     ph_target_compile_options(${name})
# endfunction()

# function(
#     ph_add_generic_vendor_interface_library
#     name
#     includes
#     libs
#     system_libs)
#     ph_add_library(${name} INTERFACE)

#     if(includes)
#         ph_target_include_directories(${name} INTERFACE ${includes})
#     endif()

#     if(libs)
#         ph_target_link_libraries(${name} INTERFACE ${libs})
#     endif()

#     if(system_libs)
#         ph_target_link_system_libraries(${name} INTERFACE ${system_libs})
#     endif()
# endfunction()

# function(
#     ph_add_generic_vendor_library
#     name
#     sources
#     includes
#     libs
#     system_libs)
#     ph_add_library(${name} STATIC ${sources})

#     if(includes)
#         ph_target_include_directories(${name} PUBLIC ${includes})
#     endif()

#     if(libs)
#         ph_target_link_libraries(${name} PUBLIC ${libs})
#     endif()

#     if(system_libs)
#         ph_target_link_system_libraries(${name} PUBLIC ${system_libs})
#     endif()

#     string(TOUPPER ${name} uppername)

#     ph_target_compile_definitions(${name} ${uppername}_BUILD)

#     ph_target_compile_features(${name})
# endfunction()

# function(
#     ph_add_generic_executable
#     name
#     sources
#     pch
#     libs
#     system_libs)
#     ph_add_executable(${name} ${sources})

#     ph_target_include_directories(${name} PRIVATE ${CMAKE_SOURCE_DIR}/include)

#     if(pch)
#         ph_target_precompile_headers(${name} PRIVATE ${pch})
#     endif()

#     if(libs)
#         ph_target_link_libraries(${name} PRIVATE ${libs})
#     endif()

#     if(system_libs)
#         ph_target_link_system_libraries(${name} PRIVATE ${system_libs})
#     endif()

#     string(TOUPPER ${name} uppername)

#     ph_target_compile_definitions(${name} ${uppername}_BUILD)

#     ph_target_compile_features(${name})

#     ph_target_compile_options(${name})
# endfunction()

# function(ph_add_generic_tests name sources)
#     ph_add_executable(test_${name} ${sources} ${CMAKE_SOURCE_DIR}/test/main.cpp)

#     ph_target_include_directories(test_${name} PRIVATE ${CMAKE_SOURCE_DIR}/include)

#     ph_target_link_libraries(
#         test_${name}
#         PRIVATE
#         ph_vendor_catch2
#         ph_vendor_trompeloeil
#         ${name})

#     string(TOUPPER ${name} uppername)

#     ph_target_compile_definitions(test_${name} ${uppername}_TESTING)

#     ph_target_compile_features(test_${name})

#     ph_target_compile_options(test_${name})

#     catch_discover_tests(test_${name} WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
# endfunction()
# cmake-format: on

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
