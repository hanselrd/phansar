#include <phansar/client/opengl/renderer.hpp>
#include <phansar/common/log.hpp>
#include <phansar/common/macros.hpp>

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

renderer::renderer(window & _window) : m_window{&_window}, m_camera{nullptr} {
    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

#ifdef GLAD_DEBUG
    glad_set_pre_callback(&glad_debug_pre_callback);
    glad_set_post_callback(&glad_debug_post_callback);
#endif

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);

    PH_LOG_INFO("OpenGL:");
    PH_LOG_INFO("  Vendor: {}", glGetString(GL_VENDOR));
    PH_LOG_INFO("  Renderer: {}", glGetString(GL_RENDERER));
    PH_LOG_INFO("  Version: {}", glGetString(GL_VERSION));
    PH_LOG_INFO("  Shading Language Version: {}", glGetString(GL_SHADING_LANGUAGE_VERSION));

    auto data = GLint{};
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &data);
    PH_LOG_INFO("  Maximum Texture Image Units: {}", data);
}

void renderer::viewport(std::size_t _x, std::size_t _y, std::size_t _width, std::size_t _height) {
    glViewport(static_cast<GLint>(_x),
               static_cast<GLint>(_y),
               static_cast<GLsizei>(_width),
               static_cast<GLsizei>(_height));
}

void renderer::clear_color(const glm::vec4 & _color) const {
    glClearColor(_color.r, _color.g, _color.b, _color.a);
}

void renderer::clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderer::begin(graphics::camera & _camera) {
    m_camera = &_camera;
}

void renderer::end() {
    m_camera = nullptr;
}

void renderer::submit(vertex_array & _va, shader & _shader, const glm::mat4 & _model) const {
    PH_ASSERT(m_camera != nullptr);

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
