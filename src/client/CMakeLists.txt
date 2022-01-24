ph_add_library(
    NAME ph_client_lib
    TYPE STATIC
    INCLUDE_DIRECTORIES PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR}
    COMPILE_DEFINITIONS PRIVATE ${default_compile_definitions}
    COMPILE_FEATURES PRIVATE ${default_compile_features}
    COMPILE_OPTIONS PRIVATE ${default_compile_options}
    SOURCES PRIVATE test.cpp # TODO: remove
    LINK_LIBRARIES
        PUBLIC
        ph_common
        ph_vendor_assimp
        ph_vendor_bgfx
        ph_vendor_glfw
        ph_vendor_glm
        # cmake-format: off
        # ph_vendor_sdl2
        # ph_vendor_sdl2_mixer
        # ph_vendor_sdl2_ttf
        # cmake-format: on
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
    DEPENDENCIES assets
    INSTALL RUNTIME DESTINATION bin)
