#include <phansar/client/opengl/index_buffer.hpp>
#include <phansar/client/opengl/macros.hpp>
#include <phansar/client/opengl/shader.hpp>
#include <phansar/client/opengl/vertex_array.hpp>
#include <phansar/client/opengl/vertex_buffer.hpp>
#include <phansar/client/opengl/vertex_buffer_layout.hpp>
#include <phansar/common/histogram.hpp>
#include <phansar/common/macros.hpp>
#include <phansar/common/python.hpp>
#include <phansar/common/system.hpp>

// NOLINTNEXTLINE(modernize-use-trailing-return-type)
PYBIND11_EMBEDDED_MODULE(phansar, m) {
    phansar::common::python::embed(m);
}

auto main(int _argc, char * _argv[]) -> int {
    phansar::common::system::init(_argc, _argv);

    if (glfwInit() == 0) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    auto * window = glfwCreateWindow(800, 600, "Phansar", nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

    PH_LOG_INFO("OpenGL Version: {}", glGetString(GL_VERSION));

    {
        auto va = phansar::client::opengl::vertex_array{};
        va.bind();

        auto vb = phansar::client::opengl::vertex_buffer<float>{
            -0.5F,
            -0.5F, // TL [0]
            -0.5F,
            0.5F, // BL [1]
            0.5F,
            0.5F, // BR [2]
            0.5F,
            -0.5F // TR [3]
        };
        vb.bind();

        auto layout = phansar::client::opengl::vertex_buffer_layout{};
        layout.push<float>(2);
        va.add_buffer(vb, layout);
        vb.unbind();

        auto ib = phansar::client::opengl::index_buffer<GLubyte>{0, 1, 3, 1, 2, 3};
        PH_LOG_INFO("ib: {} {:#06x}", ib.count(), ib.type());

        auto shader = phansar::client::opengl::shader{"assets/shaders/basic.glsl"};
        shader.bind();
        shader.set_uniform("u_color", 0.2F, 0.3F, 0.8F, 1.0F);
        shader.unbind();

        while (glfwWindowShouldClose(window) == 0) {
            glfwSwapBuffers(window);

            GL_CALL(glClearColor(0.2F, 0.3F, 0.3F, 1.0F));
            GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

            va.bind();
            ib.bind();
            shader.bind();

            GL_CALL(glDrawElements(GL_TRIANGLES, ib.count(), ib.type(), nullptr));

            glfwPollEvents();
        }
    }

    glfwTerminate();

    phansar::common::system::shutdown();

    return 0;
}
