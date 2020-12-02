#include <phansar/client/graphics/image.hpp>
#include <phansar/client/graphics/orthographic_camera.hpp>
#include <phansar/client/graphics/perspective_camera.hpp>
#include <phansar/client/graphics/renderer.hpp>
#include <phansar/client/graphics/shader.hpp>
#include <phansar/client/graphics/texture.hpp>
#include <phansar/client/window.hpp>
#include <phansar/common/macros.hpp>
#include <phansar/common/python.hpp>
#include <phansar/common/system.hpp>
#include <phansar/common/timer.hpp>

// NOLINTNEXTLINE(modernize-use-trailing-return-type)
PYBIND11_EMBEDDED_MODULE(phansar, m) {
    phansar::common::python::embed(m);
}

auto main(int _argc, char * _argv[]) -> int {
    phansar::common::system::init(_argc, _argv);

    auto window = phansar::client::window{800, 600, "Phansar"};

    auto renderer = phansar::client::graphics::renderer{window};

    struct pos_color_texcoord_vertex {
        glm::vec3     position;
        std::uint32_t color;
        glm::vec2     texcoord;
        glm::vec3     normal;
    };

    auto ms_layout = bgfx::VertexLayout{};
    ms_layout.begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
        .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float)
        .end();

    auto cube_vertices = std::array<pos_color_texcoord_vertex, 24>{{
        {{-0.5F, 0.5F, 0.5F}, {0xffffffff}, {0.0F, 1.0F}, {0.0F, 0.0F, 1.0F}},    // TL_front
        {{-0.5F, -0.5F, 0.5F}, {0xffffffff}, {0.0F, 0.0F}, {0.0F, 0.0F, 1.0F}},   // BL_front
        {{0.5F, -0.5F, 0.5F}, {0xffffffff}, {1.0F, 0.0F}, {0.0F, 0.0F, 1.0F}},    // BR_front
        {{0.5F, 0.5F, 0.5F}, {0xffffffff}, {1.0F, 1.0F}, {0.0F, 0.0F, 1.0F}},     // TR_front
        {{-0.5F, 0.5F, -0.5F}, {0xffffffff}, {0.0F, 1.0F}, {0.0F, 1.0F, 0.0F}},   //  TL_top
        {{-0.5F, 0.5F, 0.5F}, {0xffffffff}, {0.0F, 0.0F}, {0.0F, 1.0F, 0.0F}},    // BL_top
        {{0.5F, 0.5F, 0.5F}, {0xffffffff}, {1.0F, 0.0F}, {0.0F, 1.0F, 0.0F}},     // BR_top
        {{0.5F, 0.5F, -0.5F}, {0xffffffff}, {1.0F, 1.0F}, {0.0F, 1.0F, 0.0F}},    // TR_top
        {{0.5F, 0.5F, 0.5F}, {0xffffffff}, {0.0F, 1.0F}, {1.0F, 0.0F, 0.0F}},     //  TL_right
        {{0.5F, -0.5F, 0.5F}, {0xffffffff}, {0.0F, 0.0F}, {1.0F, 0.0F, 0.0F}},    // BL_right
        {{0.5F, -0.5F, -0.5F}, {0xffffffff}, {1.0F, 0.0F}, {1.0F, 0.0F, 0.0F}},   // BR_right
        {{0.5F, 0.5F, -0.5F}, {0xffffffff}, {1.0F, 1.0F}, {1.0F, 0.0F, 0.0F}},    // TR_right
        {{0.5F, 0.5F, -0.5F}, {0xffffffff}, {0.0F, 1.0F}, {0.0F, 0.0F, -1.0F}},   // TL_back
        {{0.5F, -0.5F, -0.5F}, {0xffffffff}, {0.0F, 0.0F}, {0.0F, 0.0F, -1.0F}},  // BL_back
        {{-0.5F, -0.5F, -0.5F}, {0xffffffff}, {1.0F, 0.0F}, {0.0F, 0.0F, -1.0F}}, // BR_back
        {{-0.5F, 0.5F, -0.5F}, {0xffffffff}, {1.0F, 1.0F}, {0.0F, 0.0F, -1.0F}},  // TR_back
        {{0.5F, -0.5F, 0.5F}, {0xffffffff}, {0.0F, 1.0F}, {0.0F, -1.0F, 0.0F}},   //  TL_bottom
        {{0.5F, -0.5F, -0.5F}, {0xffffffff}, {0.0F, 0.0F}, {0.0F, -1.0F, 0.0F}},  // BL_bottom
        {{-0.5F, -0.5F, -0.5F}, {0xffffffff}, {1.0F, 0.0F}, {0.0F, -1.0F, 0.0F}}, // BR_bottom
        {{-0.5F, -0.5F, 0.5F}, {0xffffffff}, {1.0F, 1.0F}, {0.0F, -1.0F, 0.0F}},  // TR_bottom
        {{-0.5F, 0.5F, -0.5F}, {0xffffffff}, {0.0F, 1.0F}, {-1.0F, 0.0F, 0.0F}},  //  TL_left
        {{-0.5F, -0.5F, -0.5F}, {0xffffffff}, {0.0F, 0.0F}, {-1.0F, 0.0F, 0.0F}}, // BL_left
        {{-0.5F, -0.5F, 0.5F}, {0xffffffff}, {1.0F, 0.0F}, {-1.0F, 0.0F, 0.0F}},  // BR_left
        {{-0.5F, 0.5F, 0.5F}, {0xffffffff}, {1.0F, 1.0F}, {-1.0F, 0.0F, 0.0F}}    // TR_left
    }};

    auto cube_indices = std::array<std::uint16_t, 36>{
        0,  1,  2,  0,  2,  3,  // front
        4,  5,  6,  4,  6,  7,  // top
        8,  9,  10, 8,  10, 11, // right
        12, 13, 14, 12, 14, 15, // back
        16, 17, 18, 16, 18, 19, // bottom
        20, 21, 22, 20, 22, 23  // left
    };

    auto point_light_positions = std::array<glm::vec3, 4>{glm::vec3{0.7F, 0.2F, 2.0F},
                                                          glm::vec3{2.3F, -3.3F, -4.0F},
                                                          glm::vec3{-4.0F, 2.0F, -12.0F},
                                                          glm::vec3{0.0F, 0.0F, -3.0F}};

    auto vbo = bgfx::createVertexBuffer(
        bgfx::makeRef(cube_vertices.data(),
                      cube_vertices.size() * sizeof(pos_color_texcoord_vertex)),
        ms_layout);
    auto ibo = bgfx::createIndexBuffer(
        bgfx::makeRef(cube_indices.data(), cube_indices.size() * sizeof(std::uint16_t)));

    auto program       = phansar::client::graphics::shader{"assets/shaders/vs_phansar.bin",
                                                     "assets/shaders/fs_phansar.bin"};
    auto light_program = phansar::client::graphics::shader{"assets/shaders/vs_phansar.bin",
                                                           "assets/shaders/fs_phansar_light.bin"};

    /* auto texture0 = phansar::client::graphics::texture{"assets/tilesets/city.png"}; */
    /* auto texture1 = phansar::client::graphics::texture{"assets/tilesets/rural.png"}; */
    auto container = phansar::client::graphics::texture{"assets/textures/container.png"};
    auto container_specular =
        phansar::client::graphics::texture{"assets/textures/container_specular.png"};
    auto container_emission =
        phansar::client::graphics::texture{"assets/textures/container_emission.jpg"};

    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x00000000 /*0x443355FF*/, 1.0F, 0);

    auto camera = phansar::client::graphics::perspective_camera{90.0F, 800.0F / 600.0F};

    auto model_position = glm::vec3{0.0F, 0.0F, -1.0F};
    auto model_rotation = glm::vec3{};
    auto model_scale    = glm::vec3{1.0F};

    auto model = glm::mat4{1.0F};
    model =
        glm::translate(glm::mat4{1.0F}, model_position) *
        glm::rotate(glm::mat4{1.0F}, glm::radians(model_rotation.x), glm::vec3{1.0F, 0.0F, 0.0F}) *
        glm::rotate(glm::mat4{1.0F}, glm::radians(model_rotation.y), glm::vec3{0.0F, 1.0F, 0.0F}) *
        glm::rotate(glm::mat4{1.0F}, glm::radians(model_rotation.z), glm::vec3{0.0F, 0.0F, 1.0F}) *
        glm::scale(glm::mat4{1.0F}, model_scale);

    auto timer = phansar::common::timer{};
    timer.start();
    while (window.open()) {
        auto delta_time = timer.elapsed_time<float>() / std::chrono::nanoseconds::period::den;
        timer.restart();

        window.update();

        if (glfwGetKey(window.get(), GLFW_KEY_ESCAPE) != 0) {
            glfwSetWindowShouldClose(window.get(), GLFW_TRUE);
        }
        if (glfwGetKey(window.get(), GLFW_KEY_W) != 0) {
            camera.position().z -= 2 * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_A) != 0) {
            camera.position().x -= 2 * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_S) != 0) {
            camera.position().z += 2 * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_D) != 0) {
            camera.position().x += 2 * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_Q) != 0) {
            camera.rotation().y += 50 * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_E) != 0) {
            camera.rotation().y -= 50 * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_Z) != 0) {
            camera.rotation().x += 50 * delta_time;
            camera.rotation().z += 50 * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_C) != 0) {
            camera.rotation().x -= 50 * delta_time;
            camera.rotation().z -= 50 * delta_time;
        }

        bgfx::touch(0);
        bgfx::setViewTransform(0,
                               glm::value_ptr(camera.view()),
                               glm::value_ptr(camera.projection()));
        model = glm::translate(glm::mat4{1.0F}, model_position) *
                glm::rotate(glm::mat4{1.0F},
                            glm::radians(model_rotation.x),
                            glm::vec3{1.0F, 0.0F, 0.0F}) *
                glm::rotate(glm::mat4{1.0F},
                            glm::radians(model_rotation.y),
                            glm::vec3{0.0F, 1.0F, 0.0F}) *
                glm::rotate(glm::mat4{1.0F},
                            glm::radians(model_rotation.z),
                            glm::vec3{0.0F, 0.0F, 1.0F}) *
                glm::scale(glm::mat4{1.0F}, model_scale);
        bgfx::setTransform(glm::value_ptr(model));
        bgfx::setVertexBuffer(0, vbo);
        bgfx::setIndexBuffer(ibo);
        program.set("u_normal", glm::inverseTranspose(glm::mat3{camera.view() * model}));
        program.set("s_material_diffuse", 0, container);
        program.set("s_material_specular", 1, container_specular);
        program.set("s_material_emission", 2, container_emission);
        /* program.set("u_material_ambient", glm::vec3{1.0f, 0.5f, 0.31f}); */
        /* program.set("u_material_diffuse", glm::vec3{1.0f, 0.5f, 0.31f}); */
        /* program.set("u_material_specular", glm::vec3{0.5f, 0.5f, 0.5f}); */
        program.set("u_material_ambient", glm::vec3{1.0F});
        program.set("u_material_diffuse", glm::vec3{1.0F});
        program.set("u_material_specular", glm::vec3{1.0F});
        program.set("u_material_shininess", 32.0F);
        program.set("u_directional_light_direction", glm::vec3{-0.2F, -1.0F, -0.3F});
        program.set("u_directional_light_ambient", glm::vec3{0.05F});
        program.set("u_directional_light_diffuse", glm::vec3{0.4F});
        program.set("u_directional_light_specular", glm::vec3{0.5F});
        program.set("u_point_light_position", point_light_positions[0]);
        program.set("u_point_light_ambient", glm::vec3{0.05F});
        program.set("u_point_light_diffuse", glm::vec3{0.8F});
        program.set("u_point_light_specular", glm::vec3{1.0F});
        program.set("u_point_light_attenuation", glm::vec3{1.0F, 0.09F, 0.032F});
        program.set("u_spot_light_position", camera.position());
        program.set("u_spot_light_direction", glm::vec3{0.0F, 0.0F, -1.0F});
        program.set("u_spot_light_ambient", glm::vec3{0.0F});
        program.set("u_spot_light_diffuse", glm::vec3{1.0F});
        program.set("u_spot_light_specular", glm::vec3{1.0F});
        program.set("u_spot_light_attenuation", glm::vec3{1.0F, 0.09F, 0.032F});
        program.set("u_spot_light_cutoff",
                    glm::vec2{glm::cos(glm::radians(12.5F)), glm::cos(glm::radians(15.0F))});
        bgfx::setState(
            BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_Z |
            BGFX_STATE_DEPTH_TEST_LESS | BGFX_STATE_MSAA |
            BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA));
        bgfx::submit(0, program.handle());
        bgfx::setTransform(
            glm::value_ptr(glm::translate(glm::mat4{1.0F}, point_light_positions[0]) *
                           glm::scale(glm::mat4{1.0F}, glm::vec3{0.2F})));
        bgfx::setVertexBuffer(0, vbo);
        bgfx::setIndexBuffer(ibo);
        bgfx::setState(
            BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_Z |
            BGFX_STATE_DEPTH_TEST_LESS | BGFX_STATE_MSAA |
            BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA));
        bgfx::submit(0, light_program.handle());
        bgfx::frame();
    }

    bgfx::destroy(ibo);
    bgfx::destroy(vbo);

    phansar::common::system::shutdown();

    return 0;
}
