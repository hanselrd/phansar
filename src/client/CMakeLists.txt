# cmake-format: off
set(sources
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
    window.cpp
    main.cpp)

set(pch
    <phansar/client/pch.hpp>)

set(libs
    ph_common)

set(system_libs
    ph_vendor_assimp
    ph_vendor_bgfx
    ph_vendor_glfw
    ph_vendor_glm)
# cmake-format: on

ph_add_generic_executable(ph_client "${sources}" "${pch}" "${libs}" "${system_libs}")

install(TARGETS ph_client RUNTIME DESTINATION bin)
