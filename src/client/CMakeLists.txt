ph_add_executable(
    NAME ph_client
    INCLUDE_DIRECTORIES PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR}
    COMPILE_FEATURES PRIVATE cxx_std_20 c_std_99
    SOURCES PRIVATE
            application.cpp
            graphics/camera.cpp
            graphics/image.cpp
            graphics/mesh.cpp
            graphics/model.cpp
            graphics/orthographic_camera.cpp
            graphics/perspective_camera.cpp
            graphics/renderer.cpp
            graphics/shader.cpp
            graphics/texture.cpp
            graphics/vertex.cpp
            python.cpp
            window.cpp
            main.cpp
    LINK_LIBRARIES
        PRIVATE
        ph_common
        ph_vendor_assimp
        ph_vendor_bgfx
        ph_vendor_glfw
        ph_vendor_glm
    INSTALL RUNTIME DESTINATION bin)
