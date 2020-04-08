function(ph_add_library name type)
    add_library(${name} ${type}
        ${ARGN})
endfunction()

function(ph_add_executable name)
    add_executable(${name}
        ${ARGN})
endfunction()

function(ph_target_include_directories name type)
    target_include_directories(${name} ${type}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${ARGN})
endfunction()

function(ph_target_link_libraries name type)
    target_link_libraries(${name} ${type}
        ${ARGN})
endfunction()

function(ph_target_link_system_libraries name type)
    set(libs ${ARGN})
    foreach(lib ${libs})
        get_target_property(lib_include_dirs ${lib} INTERFACE_INCLUDE_DIRECTORIES)
        if(lib_include_dirs)
            target_include_directories(${name} SYSTEM ${type}
                ${lib_include_dirs})
        endif()
        target_link_libraries(${name} ${type}
            ${lib})
    endforeach()
endfunction()

function(ph_target_compile_definitions name)
    target_compile_definitions(${name} PRIVATE
        ${ARGN})
endfunction()

function(ph_target_compile_features name)
    target_compile_features(${name} PRIVATE
        cxx_std_20
        c_std_99)
endfunction()

function(ph_target_compile_options name)
    target_compile_options(${name} PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:$<$<CONFIG:DEBUG>:-O0>>
        $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:$<$<OR:$<CONFIG:RELEASE>,$<CONFIG:RELWITHDEBINFO>,$<CONFIG:MINSIZEREL>>:-D_FORTIFY_SOURCE=2>>
        $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -Werror -Wpedantic -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -fno-common -Wconversion>
        $<$<CXX_COMPILER_ID:GNU>:-Wformat-overflow=2 -Wformat-truncation=2>
        $<$<CXX_COMPILER_ID:MSVC>:/Wall>)
endfunction()

function(ph_add_generic_interface_library name libs system_libs)
    ph_add_library(${name} INTERFACE)

    ph_target_include_directories(${name} INTERFACE)

    if(libs)
        ph_target_link_libraries(${name} INTERFACE
            ${libs})
    endif()

    if(system_libs)
        ph_target_link_system_libraries(${name} INTERFACE
            ${system_libs})
    endif()
endfunction()

function(ph_add_generic_library name sources libs system_libs)
    ph_add_library(${name} STATIC
        ${sources})

    ph_target_include_directories(${name} PUBLIC)

    if(libs)
        ph_target_link_libraries(${name} PUBLIC
            ${libs})
    endif()

    if(system_libs)
        ph_target_link_system_libraries(${name} PUBLIC
            ${system_libs})
    endif()

    string(TOUPPER ${name} uppername)

    ph_target_compile_definitions(${name}
        BUILD_${uppername})

    ph_target_compile_features(${name})

    ph_target_compile_options(${name})
endfunction()

function(ph_add_generic_vendor_interface_library name includes libs system_libs)
    ph_add_library(${name} INTERFACE)

    ph_target_include_directories(${name} INTERFACE
        ${includes})

    if(libs)
        ph_target_link_libraries(${name} INTERFACE
            ${libs})
    endif()

    if(system_libs)
        ph_target_link_system_libraries(${name} INTERFACE
            ${system_libs})
    endif()
endfunction()

function(ph_add_generic_vendor_library name sources includes libs system_libs)
    ph_add_library(${name} STATIC
        ${sources})

    ph_target_include_directories(${name} PUBLIC
        ${includes})

    if(libs)
        ph_target_link_libraries(${name} PUBLIC
            ${libs})
    endif()

    if(system_libs)
        ph_target_link_system_libraries(${name} PUBLIC
            ${system_libs})
    endif()

    string(TOUPPER ${name} uppername)

    ph_target_compile_definitions(${name}
        BUILD_${uppername})

    ph_target_compile_features(${name})
endfunction()

function(ph_add_generic_executable name sources libs system_libs)
    ph_add_executable(${name}
        ${sources})

    if(libs)
        ph_target_link_libraries(${name} PUBLIC
            ${libs})
    endif()

    if(system_libs)
        ph_target_link_system_libraries(${name} PUBLIC
            ${system_libs})
    endif()

    string(TOUPPER ${name} uppername)

    ph_target_compile_definitions(${name}
        BUILD_${uppername})

    ph_target_compile_features(${name})

    ph_target_compile_options(${name})
endfunction()

function(ph_add_generic_tests name sources)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

    ph_add_executable(test_${name}
        ${sources}
        ${CMAKE_SOURCE_DIR}/tests/main.cpp)

    ph_target_link_libraries(test_${name} PUBLIC
        ph_vendor_catch2
        ph_common_system
        ${name})

    string(TOUPPER ${name} uppername)

    ph_target_compile_definitions(test_${name}
        TESTING_${uppername})

    ph_target_compile_features(test_${name})

    ph_target_compile_options(test_${name})

    catch_discover_tests(test_${name}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endfunction()
