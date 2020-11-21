#include <phansar/client/window.hpp>

namespace phansar::client {
std::uint8_t window::s_instance_count = 0;

window::window(std::size_t _width, std::size_t _height, std::string_view _title) {
    if (s_instance_count == 0) {
        glfwInit();
    }

    ++s_instance_count;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    m_window = glfwCreateWindow(_width, _height, std::string{_title}.c_str(), nullptr, nullptr);
}

window::~window() {
    if (m_window != nullptr) {
        glfwDestroyWindow(m_window);
    }

    --s_instance_count;

    if (s_instance_count == 0) {
        glfwTerminate();
    }
}

auto window::open() -> bool {
    return glfwWindowShouldClose(m_window) == 0;
}

void window::poll_events() {
    glfwPollEvents();
}

auto window::get() -> GLFWwindow * {
    return m_window;
}
} // namespace phansar::client
