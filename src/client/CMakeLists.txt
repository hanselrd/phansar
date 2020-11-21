# cmake-format: off
set(sources
    graphics/camera.cpp
    opengl/buffer.cpp
    opengl/index_buffer.cpp
    opengl/renderer.cpp
    opengl/shader.cpp
    opengl/texture.cpp
    opengl/texture2d.cpp
    opengl/vertex_array.cpp
    opengl/vertex_buffer.cpp
    window.cpp
    main.cpp)

set(pch
    <phansar/client/pch.hpp>)

set(libs
    ph_common)

set(system_libs
    ph_vendor_entt
    ph_vendor_glad
    ph_vendor_glfw
    ph_vendor_glm
    ph_vendor_stb)
# cmake-format: on

ph_add_generic_executable(ph_client "${sources}" "${pch}" "${libs}" "${system_libs}")
