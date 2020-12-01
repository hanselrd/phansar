#include <phansar/client/graphics/renderer.hpp>

#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#    define GLFW_EXPOSE_NATIVE_X11
#elif BX_PLATFORM_OSX
#    define GLFW_EXPOSE_NATIVE_COCOA
#elif BX_PLATFORM_WINDOWS
#    define GLFW_EXPOSE_NATIVE_WIN32
#endif
#include <GLFW/glfw3native.h>

namespace phansar::client::graphics {
renderer::renderer(window & _window)  {
    bgfx::renderFrame();

    auto init = bgfx::Init{};
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
    init.platformData.ndt = glfwGetX11Display();
    init.platformData.nwh =
        reinterpret_cast<void *>(static_cast<uintptr_t>(glfwGetX11Window(_window.get())));
#elif BX_PLATFORM_OSX
    init.platformData.nwh = glfwGetCocoaWindow(_window.get());
#elif BX_PLATFORM_WINDOWS
    init.platformData.nwh = glfwGetWin32Window(_window.get());
#endif

    auto width  = int{0};
    auto height = int{0};
    glfwGetWindowSize(_window.get(), &width, &height);
    init.resolution.width  = width;
    init.resolution.height = height;
    init.resolution.reset  = BGFX_RESET_VSYNC;

    bgfx::init(init);

    bgfx::reset(width, height, BGFX_RESET_VSYNC);
    bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);

    glfwSetWindowSizeCallback(_window.get(), [](GLFWwindow * _window, int _width, int _height) {
        bgfx::reset(_width, _height, BGFX_RESET_VSYNC);
        bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
    });
}

renderer::~renderer() {
    bgfx::shutdown();
}
} // namespace phansar::client::graphics
