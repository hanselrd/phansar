#include <phansar/client/opengl/index_buffer.hpp>
#include <phansar/client/opengl/renderer.hpp>
#include <phansar/client/opengl/shader.hpp>
#include <phansar/client/opengl/vertex_array.hpp>
#include <phansar/client/opengl/vertex_buffer.hpp>
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

    auto renderer = phansar::client::opengl::renderer{window};

    struct vertex {
        float        position[2];
        std::uint8_t color[4];
    };

    vertex vertex_data1[] = {
        {-0.5F, -0.5F, 255, 0, 0, 255}, // TL [0]
        {-0.5F, 0.5F, 0, 255, 0, 255},  // BL [1]
        {0.5F, 0.5F, 0, 0, 255, 255},   // BR [2]
        {0.5F, -0.5F, 255, 0, 255, 255} // TR [3]
    };

    std::uint8_t indices1[] = {0, 1, 3, 1, 2, 3};

    auto vb1 = phansar::client::opengl::vertex_buffer{sizeof(vertex_data1), vertex_data1};
    auto ib1 = phansar::client::opengl::index_buffer{sizeof(indices1) / sizeof(std::uint8_t),
                                                     GL_UNSIGNED_BYTE,
                                                     indices1};

    auto va1 = phansar::client::opengl::vertex_array{vb1, ib1};
    va1.push_attribute(&vertex::position);
    va1.push_attribute(&vertex::color, true);

    vertex vertex_data2[] = {
        {-0.2F, -0.2F, 100, 0, 0, 100}, // TL [0]
        {-0.2F, 0.2F, 0, 100, 0, 100},  // BL [1]
        {0.2F, 0.2F, 0, 0, 100, 100},   // BR [2]
        {0.2F, -0.2F, 100, 0, 100, 100} // TR [3]
    };

    std::uint8_t indices2[] = {1, 2, 3};

    auto vb2 = phansar::client::opengl::vertex_buffer{sizeof(vertex_data2), vertex_data2};
    auto ib2 = phansar::client::opengl::index_buffer{sizeof(indices2) / sizeof(std::uint8_t),
                                                     GL_UNSIGNED_BYTE,
                                                     indices2};

    auto va2 = phansar::client::opengl::vertex_array{vb2, ib2};
    va2.push_attribute(&vertex::position);
    va2.push_attribute(&vertex::color, true);

    auto camera_proj     = glm::mat4{glm::ortho(-2.0F, 2.0F, -2.0F, 2.0F, -1.0F, 1.0F)};
    auto camera_view     = glm::mat4{};
    auto camera_position = glm::vec3{};
    auto camera_rotation = float{20.0F};

    auto transform =
        glm::translate(glm::mat4{1.0F}, camera_position) *
        glm::rotate(glm::mat4{1.0F}, glm::radians(camera_rotation), glm::vec3{0.0F, 0.0F, 1.0F});
    camera_view                 = glm::inverse(transform);
    auto camera_view_projection = glm::mat4{camera_proj * camera_view};

    auto shader = phansar::client::opengl::shader{"assets/shaders/basic.glsl"};
    shader.uniform("u_color", glm::vec4{0.2F, 0.3F, 0.8F, 1.0F});
    shader.uniform("u_view_projection", camera_view_projection);

    renderer.clear_color(glm::vec4{0.2F, 0.3F, 0.3F, 1.0F});

    auto timer = phansar::common::timer{};
    timer.start();
    while (window.open()) {
        auto delta_time = timer.elapsed_time<float>() / std::chrono::nanoseconds::period::den;
        timer.restart();

        window.poll_events();

        if (glfwGetKey(window.get(), GLFW_KEY_LEFT)) {
            camera_position.x -= 2 * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_RIGHT)) {
            camera_position.x += 2 * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_UP)) {
            camera_position.y += 2 * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_DOWN)) {
            camera_position.y -= 2 * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_A)) {
            camera_rotation += 50 * delta_time;
        }
        if (glfwGetKey(window.get(), GLFW_KEY_D)) {
            camera_rotation -= 50 * delta_time;
        }

        renderer.clear();

        transform = glm::translate(glm::mat4{1.0F}, camera_position) *
                    glm::rotate(glm::mat4{1.0F},
                                glm::radians(camera_rotation),
                                glm::vec3{0.0F, 0.0F, 1.0F});
        camera_view            = glm::inverse(transform);
        camera_view_projection = glm::mat4{camera_proj * camera_view};

        renderer.begin();
        shader.uniform("u_view_projection", camera_view_projection);
        renderer.submit(va1, shader);
        renderer.submit(va2, shader);
        renderer.end();

        renderer.swap_buffers();
    }

    phansar::common::system::shutdown();

    return 0;
}
