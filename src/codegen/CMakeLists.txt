ph_add_executable(
    NAME ph_codegen
    INCLUDE_DIRECTORIES PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR}
    COMPILE_DEFINITIONS PRIVATE ${default_compile_definitions}
    COMPILE_FEATURES PRIVATE ${default_compile_features}
    COMPILE_OPTIONS PRIVATE ${default_compile_options}
    SOURCES PRIVATE codegen.cpp
    LINK_LIBRARIES PRIVATE ph_vendor_fmt ph_vendor_llvm
    SANITIZERS ${default_sanitizers})
