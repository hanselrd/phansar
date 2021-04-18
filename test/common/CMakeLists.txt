ph_add_executable(
    NAME test_ph_common
    INCLUDE_DIRECTORIES PRIVATE ${CMAKE_SOURCE_DIR}/include
    COMPILE_FEATURES PRIVATE cxx_std_20 c_std_99
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
    DISCOVER_TESTS WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
