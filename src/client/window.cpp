#include <phansar/client/window.hpp>
#define PH_VENDOR_GLFW_PRIVATE
#include <phansar/vendor/glfw.hpp>

namespace phansar::client {
struct window::impl {
    GLFWwindow * window;

    static std::uint8_t s_instance_count;
};

std::uint8_t window::impl::s_instance_count = 0;

window::window(std::size_t _width, std::size_t _height, std::string_view _title) : m_impl{nullptr} {
    if (m_impl->s_instance_count == 0) {
        glfwInit();
    }

    ++m_impl->s_instance_count;

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    m_impl->window = glfwCreateWindow(static_cast<int>(_width),
                                      static_cast<int>(_height),
                                      std::string{_title}.c_str(),
                                      nullptr,
                                      nullptr);
}

window::~window() {
    if (m_impl->window != nullptr) {
        glfwDestroyWindow(m_impl->window);
    }

    --m_impl->s_instance_count;

    if (m_impl->s_instance_count == 0) {
        glfwTerminate();
    }
}

auto window::open() -> bool {
    return glfwWindowShouldClose(m_impl->window) == 0;
}

void window::update() {
    glfwPollEvents();
}

auto window::ndt() -> void * {
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
    return glfwGetX11Display();
#else
    return nullptr;
#endif
}

auto window::nwh() -> void * {
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
    return reinterpret_cast<void *>(static_cast<uintptr_t>(glfwGetX11Window(m_impl->window)));
#elif BX_PLATFORM_OSX
    return glfwGetCocoaWindow(m_impl->window);
#elif BX_PLATFORM_WINDOWS
    return glfwGetWin32Window(m_impl->window);
#else
    return nullptr;
#endif
}
} // namespace phansar::client
