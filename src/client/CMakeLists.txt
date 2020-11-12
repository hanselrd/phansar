# cmake-format: off
set(sources
    opengl/shader.cpp
    opengl/vertex_array.cpp
    opengl/vertex_buffer_layout.cpp
    main.cpp)

set(pch
    <phansar/client/pch.hpp>)

set(libs
    ph_common)

set(system_libs
    ph_vendor_entt
    ph_vendor_glad
    ph_vendor_glfw
    ph_vendor_stb)
# cmake-format: on

ph_add_generic_executable(ph_client "${sources}" "${pch}" "${libs}" "${system_libs}")
