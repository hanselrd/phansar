#include <phansar/client/graphics/renderer.hpp>
#include <phansar/common/macros.hpp>

namespace phansar::client::graphics {
struct renderer::impl {
    camera * cam;
};

renderer::renderer(window & _window) : m_impl{nullptr} {
    bgfx::renderFrame();

    auto init = bgfx::Init{};
    /* #if BX_PLATFORM_LINUX || BX_PLATFORM_BSD */
    /*     init.platformData.ndt = glfwGetX11Display(); */
    /*     init.platformData.nwh = */
    /*         reinterpret_cast<void *>(static_cast<uintptr_t>(glfwGetX11Window(_window.get()))); */
    /* #elif BX_PLATFORM_OSX */
    /*     init.platformData.nwh = glfwGetCocoaWindow(_window.get()); */
    /* #elif BX_PLATFORM_WINDOWS */
    /*     init.platformData.nwh = glfwGetWin32Window(_window.get()); */
    /* #endif */
    init.platformData.ndt = _window.ndt();
    init.platformData.nwh = _window.nwh();

    auto width  = int{0};
    auto height = int{0};
    // TODO: get size from window using events
    /* glfwGetWindowSize(_window.get(), &width, &height); */
    init.resolution.width  = static_cast<std::uint32_t>(width);
    init.resolution.height = static_cast<std::uint32_t>(height);
    init.resolution.reset  = BGFX_RESET_VSYNC;

    bgfx::init(init);

#ifdef PH_BUILD_DEBUG
    bgfx::setDebug(BGFX_DEBUG_TEXT);
#endif

    bgfx::reset(static_cast<std::uint32_t>(width),
                static_cast<std::uint32_t>(height),
                BGFX_RESET_VSYNC);
    bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);

    /* glfwSetWindowSizeCallback(_window.get(), [](GLFWwindow *, int _width, int _height) { */
    /*     bgfx::reset(static_cast<std::uint32_t>(_width), */
    /*                 static_cast<std::uint32_t>(_height), */
    /*                 BGFX_RESET_VSYNC); */
    /*     bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal); */
    /* }); */
}

renderer::~renderer() {
    bgfx::shutdown();
}

void renderer::view_clear(std::uint32_t _rgba, float _depth, std::uint8_t _stencil) {
    bgfx::setViewClear(0,
                       BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL,
                       _rgba,
                       _depth,
                       _stencil);
}

void renderer::touch() {
    bgfx::touch(0);
}

void renderer::begin(camera & _camera) {
    PH_ASSERT(! m_impl->cam);

    m_impl->cam = &_camera;
}

void renderer::submit(const mesh &      _mesh,
                      shader &          _shader,
                      const glm::mat4 & _model,
                      std::uint32_t     _depth,
                      std::uint32_t     _stencil,
                      std::uint64_t     _state,
                      std::uint8_t      _flags) {
    PH_ASSERT(m_impl->cam);
    PH_ASSERT(bgfx::isValid(_mesh.vbo_handle()));

    bgfx::setViewTransform(0,
                           glm::value_ptr(m_impl->cam->view()),
                           glm::value_ptr(m_impl->cam->projection()));
    bgfx::setTransform(glm::value_ptr(_model));

    bgfx::setVertexBuffer(0, _mesh.vbo_handle());
    if (bgfx::isValid(_mesh.ibo_handle())) {
        bgfx::setIndexBuffer(_mesh.ibo_handle());
    }

    bgfx::setStencil(_stencil);
    bgfx::setState(_state);

    _shader.set("u_normal", glm::inverseTranspose(glm::mat3{m_impl->cam->view() * _model}));
    bgfx::submit(0, _shader.handle(), _depth, _flags);
}

void renderer::end() {
    PH_ASSERT(m_impl->cam);

    m_impl->cam = nullptr;
}

void renderer::flush() {
    PH_ASSERT(! m_impl->cam);

    bgfx::frame();
}
} // namespace phansar::client::graphics
