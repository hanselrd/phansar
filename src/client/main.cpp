#include <phansar/client/graphics/orthographic_camera.hpp>
#include <phansar/client/opengl/index_buffer.hpp>
#include <phansar/client/opengl/renderer.hpp>
#include <phansar/client/opengl/shader.hpp>
#include <phansar/client/opengl/texture2d.hpp>
#include <phansar/client/opengl/vertex_array.hpp>
#include <phansar/client/opengl/vertex_buffer.hpp>
#include <phansar/client/window.hpp>
#include <phansar/common/macros.hpp>
#include <phansar/common/python.hpp>
#include <phansar/common/ref.hpp>
#include <phansar/common/system.hpp>
#include <phansar/common/timer.hpp>

// NOLINTNEXTLINE(modernize-use-trailing-return-type)
PYBIND11_EMBEDDED_MODULE(phansar, m) {
    phansar::common::python::embed(m);
}

auto main(int _argc, char * _argv[]) -> int {
    phansar::common::system::init(_argc, _argv);

    auto window = phansar::client::window{800, 600, "Phansar"};

    auto renderer = phansar::client::opengl::renderer{window};
    renderer.viewport(0, 0, 800, 600);

    glfwSetWindowUserPointer(window.get(), &renderer);

    glfwSetWindowSizeCallback(window.get(), [](GLFWwindow * _window, int _width, int _height) {
        auto * renderer = reinterpret_cast<phansar::client::opengl::renderer *>(
            glfwGetWindowUserPointer(_window));
        renderer->viewport(0, 0, _width, _height);
    });

    struct vertex {
        float position[2];
        float texcoord[2];
    };

    vertex vertex_data1[] = {
        {-0.5F, -0.5F, 0.0F, 0.0F}, // TL [0]
        {-0.5F, 0.5F, 0.0F, 1.0F},  // BL [1]
        {0.5F, 0.5F, 1.0F, 1.0F},   // BR [2]
        {0.5F, -0.5F, 1.0F, 0.0F}   // TR [3]
    };

    std::uint8_t indices1[] = {0, 1, 3, 1, 2, 3};

    auto vb1 = phansar::client::opengl::vertex_buffer{sizeof(vertex_data1), vertex_data1};
    auto ib1 = phansar::client::opengl::index_buffer{sizeof(indices1) / sizeof(std::uint8_t),
                                                     GL_UNSIGNED_BYTE,
                                                     indices1};

    auto va1 = phansar::client::opengl::vertex_array{vb1, ib1};
    va1.push_attribute(&vertex::position);
    va1.push_attribute(&vertex::texcoord); // TODO: fix

    /* vertex vertex_data2[] = { */
    /*     {-0.2F, -0.2F, 100, 0, 0, 100}, // TL [0] */
    /*     {-0.2F, 0.2F, 0, 100, 0, 100},  // BL [1] */
    /*     {0.2F, 0.2F, 0, 0, 100, 100},   // BR [2] */
    /*     {0.2F, -0.2F, 100, 0, 100, 100} // TR [3] */
    /* }; */

    /* std::uint8_t indices2[] = {1, 2, 3}; */

    /* auto vb2 = phansar::client::opengl::vertex_buffer{sizeof(vertex_data2), vertex_data2}; */
    /* auto ib2 = phansar::client::opengl::index_buffer{sizeof(indices2) / sizeof(std::uint8_t), */
    /*                                                  GL_UNSIGNED_BYTE, */
    /*                                                  indices2}; */

    /* auto va2 = phansar::client::opengl::vertex_array{vb2, ib2}; */
    /* va2.push_attribute(&vertex::position); */
    /* va2.push_attribute(&vertex::color, true); */

    auto aspect_ratio = 800.0F / 600.0F;
    auto zoom         = 1.0F;
    auto camera       = phansar::client::graphics::orthographic_camera{-aspect_ratio * zoom,
                                                                 aspect_ratio * zoom,
                                                                 -zoom,
                                                                 zoom};

    auto texture = phansar::client::opengl::texture2d{"assets/tilesets/city.png"};

    auto shader = phansar::client::opengl::shader{"assets/shaders/texture.glsl"};
    /* shader.uniform("u_color", glm::vec4{0.2F, 0.3F, 0.8F, 1.0F}); */
    shader.uniform("u_texture", 0);

    /* renderer.clear_color(glm::vec4{0.2F, 0.3F, 0.3F, 1.0F}); */
    renderer.clear_color(glm::vec4{0.0F, 0.0F, 0.0F, 0.0F});

    auto timer = phansar::common::timer{};
    timer.start();
    while (window.open()) {
        auto delta_time = timer.elapsed_time<float>() / std::chrono::nanoseconds::period::den;
        timer.restart();

        if (glfwGetKey(window.get(), GLFW_KEY_A) != 0) {
            camera.position().x -= 2 * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_D) != 0) {
            camera.position().x += 2 * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_W) != 0) {
            camera.position().y += 2 * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_S) != 0) {
            camera.position().y -= 2 * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_Q) != 0) {
            camera.rotation() += 50 * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_E) != 0) {
            camera.rotation() -= 50 * delta_time;
        }

        renderer.clear();

        renderer.begin(camera);
        texture.bind();
        renderer.submit(va1, shader, glm::scale(glm::mat4{1.0F}, glm::vec3{1.5F, 1.5F, 1.0F}));
        /* renderer.submit(va2, shader); */
        renderer.end();

        window.update();
    }

    phansar::common::system::shutdown();

    return 0;
}
