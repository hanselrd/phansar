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

    auto cube_vertices = std::array<pos_color_texcoord_vertex, 4>{
        {{{-0.5F, 0.5F, 0.0F}, {0xffffffff}, {0.0F, 1.0F}, {0.0F, 0.0F, -1.0F}},
         {{-0.5F, -0.5F, 0.0F}, {0xffffffff}, {0.0F, 0.0F}, {0.0F, 0.0F, -1.0F}},
         {{0.5F, -0.5F, 0.0F}, {0xffffffff}, {1.0F, 0.0F}, {0.0F, 0.0F, -1.0F}},
         {{0.5F, 0.5F, 0.0F}, {0xffffffff}, {1.0F, 1.0F}, {0.0F, 0.0F, -1.0F}}}};

    auto cube_indices = std::array<std::uint16_t, 6>{0, 1, 2, 0, 2, 3};

    auto vbo = bgfx::createVertexBuffer(
        bgfx::makeRef(cube_vertices.data(),
                      cube_vertices.size() * sizeof(pos_color_texcoord_vertex)),
        ms_layout);
    auto ibo = bgfx::createIndexBuffer(
        bgfx::makeRef(cube_indices.data(), cube_indices.size() * sizeof(std::uint16_t)));

    auto program = phansar::client::graphics::shader{"assets/shaders/vs_phansar.bin",
                                                     "assets/shaders/fs_phansar.bin"};

    auto texture0 = phansar::client::graphics::texture{"assets/tilesets/city.png"};
    auto texture1 = phansar::client::graphics::texture{"assets/tilesets/rural.png"};

    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x00000000 /*0x443355FF*/, 1.0F, 0);

    auto camera = phansar::client::graphics::perspective_camera{90.0F, 800.0F / 600.0F};

    auto model_position = glm::vec3{};
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
            model_position.z -= 2 * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_A) != 0) {
            model_position.x -= 2 * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_S) != 0) {
            model_position.z += 2 * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_D) != 0) {
            model_position.x += 2 * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_Q) != 0) {
            model_rotation.y += 50 * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_E) != 0) {
            model_rotation.y -= 50 * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_Z) != 0) {
            model_scale.x += 0.4F * delta_time;
            model_scale.y += 0.4F * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_C) != 0) {
            model_scale.x -= 0.4F * delta_time;
            model_scale.y -= 0.4F * delta_time;
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
        program.set("s_material_diffuse", 0, texture0);
        program.set("s_material_specular", 1, texture1);
        program.set("u_material_ambient", glm::vec3{0.1F});
        program.set("u_material_diffuse", glm::vec3{1.0F});
        program.set("u_material_specular", glm::vec3{2.0F});
        program.set("u_material_tint", glm::vec4{1.0F});
        program.set("u_light_position", glm::vec3{0.0F, 0.0F, 1.0F});
        program.set("u_camera_position", camera.position());
        bgfx::setState(
            BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_Z |
            BGFX_STATE_DEPTH_TEST_LESS | BGFX_STATE_MSAA |
            BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA));
        bgfx::submit(0, program.handle());
        bgfx::frame();
    }

    bgfx::destroy(ibo);
    bgfx::destroy(vbo);

    phansar::common::system::shutdown();

    return 0;
}
