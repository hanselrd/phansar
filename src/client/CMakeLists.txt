ph_add_library(
    NAME ph_client_lib
    INCLUDE_DIRECTORIES PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR}
    COMPILE_DEFINITIONS PRIVATE ${default_compile_definitions}
    COMPILE_FEATURES PRIVATE ${default_compile_features}
    COMPILE_OPTIONS PRIVATE ${default_compile_options}
    SOURCES PRIVATE test.cpp
    LINK_LIBRARIES
        PUBLIC
        ph_common
        ph_vendor_assimp
        ph_vendor_bgfx
        ph_vendor_glfw
        ph_vendor_glm
    SANITIZERS ${default_sanitizers})

ph_add_executable(
    NAME ph_client
    INCLUDE_DIRECTORIES PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR}
    COMPILE_DEFINITIONS PRIVATE ${default_compile_definitions}
    COMPILE_FEATURES PRIVATE ${default_compile_features}
    COMPILE_OPTIONS PRIVATE ${default_compile_options}
    SOURCES PRIVATE main.cpp
    LINK_LIBRARIES PRIVATE ph_client_lib
    SANITIZERS ${default_sanitizers}
    INSTALL RUNTIME DESTINATION bin)
