#include <phansar/client/application.hpp>
/* #include <phansar/common/command_line.hpp> */
/* #include <phansar/common/macros.hpp> */
/* #include <phansar/client/graphics/image.hpp> */
/* #include <phansar/client/graphics/model.hpp> */
/* #include <phansar/client/graphics/orthographic_camera.hpp> */
/* #include <phansar/client/graphics/perspective_camera.hpp> */
/* #include <phansar/client/graphics/renderer.hpp> */
/* #include <phansar/client/graphics/shader.hpp> */
/* #include <phansar/client/graphics/texture.hpp> */
/* #include <phansar/client/graphics/vertex.hpp> */
/* #include <phansar/client/window.hpp> */
/* #include <phansar/common/python.hpp> */
/* #include <phansar/common/timer.hpp> */
#include <phansar/vendor/pybind11.hpp>

auto main(int _argc, char * _argv[]) -> int {
    /* auto app = phansar::client::application{_argc, _argv}; */
    /* app.run(); */

    auto guard = py::scoped_interpreter{};
    py::exec(R"python(
        from phansar import histogram

        h = histogram("Python", "bits", 10)
        h.push(10.2)
        h.push(11)
        h.push(1)
        h.push(3)
        print(h.name)
        print(h.bins)
        print(h.samples)
        print(h.variance)
        print(h.standard_deviation)
        print(h)
    )python");

#if 0
    auto window = phansar::client::window{800, 600, "Service"};

    auto renderer = phansar::client::graphics::renderer{window};

    auto model     = phansar::client::graphics::model{"assets/models/backpack/backpack.obj"};
    auto icosphere = phansar::client::graphics::model{"assets/models/icosphere/Ico.fbx.fbx"};

    auto point_light_positions = std::array<glm::vec3, 4>{glm::vec3{0.7F, 0.2F, 2.0F},
                                                          glm::vec3{2.3F, -3.3F, -4.0F},
                                                          glm::vec3{-4.0F, 2.0F, -12.0F},
                                                          glm::vec3{0.0F, 0.0F, -3.0F}};

    auto program = phansar::client::graphics::shader{"assets/shaders/glsl/vs_phansar.bin",
                                                     "assets/shaders/glsl/fs_phansar.bin"};
    auto flat_program =
        phansar::client::graphics::shader{"assets/shaders/glsl/vs_phansar.bin",
                                          "assets/shaders/glsl/fs_phansar_flat.bin"};

    /* auto texture0 = phansar::client::graphics::texture{"assets/tilesets/city.png"}; */
    /* auto texture1 = phansar::client::graphics::texture{"assets/tilesets/rural.png"}; */
    auto container = phansar::client::graphics::texture{"assets/textures/container.png"};
    auto container_specular =
        phansar::client::graphics::texture{"assets/textures/container_specular.png"};
    auto container_emissive =
        phansar::client::graphics::texture{"assets/textures/container_emissive.jpg"};
    auto white_pixel   = std::uint32_t{0xFFFFFFFF};
    auto black_pixel   = std::uint32_t{0x00000000};
    auto white_texture = phansar::client::graphics::texture{1,
                                                            1,
                                                            bgfx::TextureFormat::RGBA8,
                                                            &white_pixel,
                                                            sizeof(std::uint32_t)};
    auto black_texture = phansar::client::graphics::texture{1,
                                                            1,
                                                            bgfx::TextureFormat::RGBA8,
                                                            &black_pixel,
                                                            sizeof(std::uint32_t)};

    renderer.view_clear(0x123456FF);

    auto camera = phansar::client::graphics::perspective_camera{90.0F, 800.0F / 600.0F};

    auto model_position = glm::vec3{0.0F, 0.0F, -1.0F};
    auto model_rotation = glm::vec3{};
    auto model_scale    = glm::vec3{0.6F};

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

        renderer.touch();

        renderer.begin(camera);
        /* program.set("s_material_diffuse", 0, container); */
        /* program.set("s_material_specular", 1, container_specular); */
        /* program.set("s_material_emissive", 2, container_emissive); */
        program.set("s_material_diffuse", 0, white_texture);
        program.set("s_material_specular", 1, white_texture);
        program.set("s_material_emissive", 2, black_texture);
        program.set("u_material_ambient", glm::vec3{0.2F, 0.2F, 0.2F});
        program.set("u_material_diffuse", glm::vec3{1.0F, 0.2F, 0.2F});
        program.set("u_material_specular", glm::vec3{1.0F, 1.0F, 1.0F});
        program.set("u_material_shininess", 48.0F);
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
        program.set("u_spot_light_direction", camera.direction());
        program.set("u_spot_light_ambient", glm::vec3{0.0F});
        program.set("u_spot_light_diffuse", glm::vec3{1.0F});
        program.set("u_spot_light_specular", glm::vec3{1.0F});
        program.set("u_spot_light_attenuation", glm::vec3{1.0F, 0.09F, 0.032F});
        program.set("u_spot_light_cutoff",
                    glm::vec2{glm::cos(glm::radians(12.5F)), glm::cos(glm::radians(15.0F))});
        for (const auto & mesh : icosphere.meshes()) {
            renderer.submit(mesh,
                            program,
                            glm::translate(glm::mat4{1.0F}, model_position) *
                                glm::rotate(glm::mat4{1.0F},
                                            glm::radians(model_rotation.x),
                                            glm::vec3{1.0F, 0.0F, 0.0F}) *
                                glm::rotate(glm::mat4{1.0F},
                                            glm::radians(model_rotation.y),
                                            glm::vec3{0.0F, 1.0F, 0.0F}) *
                                glm::rotate(glm::mat4{1.0F},
                                            glm::radians(model_rotation.z),
                                            glm::vec3{0.0F, 0.0F, 1.0F}) *
                                glm::scale(glm::mat4{1.0F}, model_scale));
        }
        for (auto i = std::size_t{0}; i < point_light_positions.size(); ++i) {
            flat_program.set("u_material_color", glm::vec4{point_light_positions[i], 1.0F});
            for (const auto & mesh : icosphere.meshes()) {
                renderer.submit(mesh,
                                flat_program,
                                glm::translate(glm::mat4{1.0F}, point_light_positions[i]) *
                                    glm::scale(glm::mat4{1.0F}, glm::vec3{0.2F}));
            }
        }
        for (const auto & mesh : model.meshes()) {
            renderer.submit(
                mesh,
                program,
                 glm::translate(glm::mat4{1.0F}, model_position - glm::vec3{-2.0F, 0.0F, 0.0F}) *
                    glm::scale(glm::mat4{1.0F}, glm::vec3{0.2F}));
        }
        renderer.end();

        renderer.flush();
    }

    /* auto process_reader = bx::ProcessReader(); */
    /* (void)process_reader; */
#endif

    return 0;
}
