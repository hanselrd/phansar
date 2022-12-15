ph_add_executable(
    NAME test_ph_vendor
    COMPILE_DEFINITIONS PRIVATE ${default_compile_definitions}
    COMPILE_FEATURES PRIVATE ${default_compile_features}
    COMPILE_OPTIONS PRIVATE ${default_compile_options}
    SOURCES PRIVATE ${CMAKE_SOURCE_DIR}/test/main.cpp sigslot.unittest.cpp
    LINK_LIBRARIES
        PRIVATE
        ph_vendor_catch2
        ph_vendor_sigslot
        ph_vendor_trompeloeil
    SANITIZERS ${default_sanitizers}
    DISCOVER_TESTS WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
