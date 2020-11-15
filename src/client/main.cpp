#include <phansar/client/opengl/shader.hpp>
#include <phansar/client/opengl/vertex_array.hpp>
#include <phansar/common/histogram.hpp>
#include <phansar/common/macros.hpp>
#include <phansar/common/python.hpp>
#include <phansar/common/system.hpp>

#ifdef GLAD_DEBUG
static void glad_debug_pre_callback(const char * _name, void * _funcptr, int _len_args, ...) {
    while (glad_glGetError() != GL_NO_ERROR) {
    }
    phansar::common::log::instance()
        ->print(phansar::common::log::level::trace, "<opengl>", 0, "{} <{}>", _name, _funcptr);
}

static void glad_debug_post_callback(const char * _name, void * _funcptr, int _len_args, ...) {
    if (auto error = glad_glGetError(); error != GL_NO_ERROR) {
        phansar::common::log::instance()->print(phansar::common::log::level::critical,
                                                "<opengl>",
                                                0,
                                                "{} ({:#0{}x}) <{}>",
                                                _name,
                                                error,
                                                sizeof(error) + 2,
                                                _funcptr);
        std::terminate();
    }
}
#endif

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

#ifdef GLAD_DEBUG
    glad_set_pre_callback(&glad_debug_pre_callback);
    glad_set_post_callback(&glad_debug_post_callback);
#endif

    PH_LOG_INFO("██████╗ ██╗  ██╗ █████╗ ███╗   ██╗███████╗ █████╗ ██████╗ ");
    PH_LOG_INFO("██╔══██╗██║  ██║██╔══██╗████╗  ██║██╔════╝██╔══██╗██╔══██╗");
    PH_LOG_INFO("██████╔╝███████║███████║██╔██╗ ██║███████╗███████║██████╔╝");
    PH_LOG_INFO("██╔═══╝ ██╔══██║██╔══██║██║╚██╗██║╚════██║██╔══██║██╔══██╗");
    PH_LOG_INFO("██║     ██║  ██║██║  ██║██║ ╚████║███████║██║  ██║██║  ██║");
    PH_LOG_INFO("╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝");

    PH_LOG_INFO("OpenGL:");
    PH_LOG_INFO("  Vendor: {}", glGetString(GL_VENDOR));
    PH_LOG_INFO("  Renderer: {}", glGetString(GL_RENDERER));
    PH_LOG_INFO("  Version: {}", glGetString(GL_VERSION));
    PH_LOG_INFO("  Shading Language Version: {}", glGetString(GL_SHADING_LANGUAGE_VERSION));

    {
        struct vertex {
            float        position[2];
            std::uint8_t color[4];
        };

        auto va = phansar::client::opengl::vertex_array<vertex, 10000, 40000>{
            {
                {-0.5F, -0.5F, 255, 0, 0, 255}, // TL [0]
                {-0.5F, 0.5F, 0, 255, 0, 255},  // BL [1]
                {0.5F, 0.5F, 0, 0, 255, 255},   // BR [2]
                {0.5F, -0.5F, 255, 0, 255, 255} // TR [3]
            },
            {0, 1, 3, 1, 2, 3}};
        va.push_attribute(&vertex::position);
        va.push_attribute(&vertex::color, true);

        auto shader = phansar::client::opengl::shader{"assets/shaders/basic.glsl"};
        shader.bind();
        shader.set_uniform("u_color", 0.2F, 0.3F, 0.8F, 1.0F);
        shader.unbind();

        while (glfwWindowShouldClose(window) == 0) {
            glfwSwapBuffers(window);

            glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
            glClear(GL_COLOR_BUFFER_BIT);

            va.bind();
            shader.bind();

            glDrawElements(GL_TRIANGLES, va.indices().size(), va.type(), nullptr);

            glfwPollEvents();
        }
    }

    glfwTerminate();

    phansar::common::system::shutdown();

    return 0;
}
