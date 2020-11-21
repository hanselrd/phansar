#include <phansar/client/opengl/renderer.hpp>
#include <phansar/common/log.hpp>

namespace phansar::client::opengl {
#ifdef GLAD_DEBUG
static void glad_debug_pre_callback(const char * _name, void * _funcptr, int _len_args, ...) {
    while (glad_glGetError() != GL_NO_ERROR) {
    }
    common::log::instance()
        ->print(common::log::level::trace, "<opengl>", 0, "{} <{}>", _name, _funcptr);
}

static void glad_debug_post_callback(const char * _name, void * _funcptr, int _len_args, ...) {

    if (auto error = glad_glGetError(); error != GL_NO_ERROR) {
        common::log::instance()->print(common::log::level::critical,
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

renderer::renderer(window & _window) : m_window{&_window} {
    glfwMakeContextCurrent(m_window->get());
    glfwSwapInterval(1);

    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

#ifdef GLAD_DEBUG
    glad_set_pre_callback(&glad_debug_pre_callback);
    glad_set_post_callback(&glad_debug_post_callback);
#endif

    PH_LOG_INFO("OpenGL:");
    PH_LOG_INFO("  Vendor: {}", glGetString(GL_VENDOR));
    PH_LOG_INFO("  Renderer: {}", glGetString(GL_RENDERER));
    PH_LOG_INFO("  Version: {}", glGetString(GL_VERSION));
    PH_LOG_INFO("  Shading Language Version: {}", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void renderer::clear_color(const glm::vec4 & _color) const {
    glClearColor(_color.r, _color.g, _color.b, _color.a);
}

void renderer::clear() const {
    glClear(GL_COLOR_BUFFER_BIT);
}

void renderer::swap_buffers() const {
    glfwSwapBuffers(m_window->get());
}

void renderer::begin() const {}

void renderer::end() const {}

void renderer::submit(vertex_array & _va, shader & _shader) const {
    _va.bind();
    _shader.bind();

    glDrawElements(GL_TRIANGLES, _va.indices().count(), _va.indices().type(), nullptr);
}
} // namespace phansar::client::opengl
