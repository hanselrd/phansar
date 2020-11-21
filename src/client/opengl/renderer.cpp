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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderer::swap_buffers() const {
    glfwSwapBuffers(m_window->get());
}

void renderer::begin(graphics::camera & _camera) {
    m_camera = &_camera;
}

void renderer::end() {
    m_camera = nullptr;
}

void renderer::submit(vertex_array & _va, shader & _shader, const glm::mat4 & _model) const {
    _va.bind();
    _shader.bind();

    _shader.uniform("u_model", _model);
    if (m_camera != nullptr) {
        _shader.uniform("u_view", m_camera->view());
        _shader.uniform("u_projection", m_camera->projection());
    }

    glDrawElements(GL_TRIANGLES, _va.indices().count(), _va.indices().type(), nullptr);
}
} // namespace phansar::client::opengl
