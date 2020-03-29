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
        ${CMAKE_CURRENT_SOURCE_DIR}/include)
endfunction()

function(ph_target_link_libraries name type)
    target_link_libraries(${name} ${type}
        ${ARGN})
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
        $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -Werror -pedantic>
        $<$<CXX_COMPILER_ID:MSVC>:/Wall>)
endfunction()

function(ph_add_generic_interface_library name libs)
    ph_add_library(${name} INTERFACE)

    ph_target_include_directories(${name} INTERFACE)

    if(libs)
        ph_target_link_libraries(${name} INTERFACE
            ${libs})
    endif()
endfunction()

function(ph_add_generic_library name sources libs)
    ph_add_library(${name} STATIC
        ${sources})

    ph_target_include_directories(${name} PUBLIC)

    if(libs)
        ph_target_link_libraries(${name} PUBLIC
            ${libs})
    endif()

    string(TOUPPER ${name} uppername)

    ph_target_compile_definitions(${name}
        BUILD_${uppername})

    ph_target_compile_features(${name})

    ph_target_compile_options(${name})
endfunction()

function(ph_add_generic_executable name sources libs)
    ph_add_executable(${name}
        ${sources})

    if(libs)
        ph_target_link_libraries(${name} PUBLIC
            ${libs})
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
        Catch2
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
