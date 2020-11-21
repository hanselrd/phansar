#include <phansar/client/graphics/camera.hpp>

namespace phansar::client::graphics {
camera::camera(const glm::mat4 & _projection) : m_projection{_projection}, m_position{0.0F} {}

auto camera::view() -> const glm::mat4 & {
    m_view = glm::inverse(
        glm::translate(glm::mat4{1.0F}, m_position) *
        glm::rotate(glm::mat4{1.0F}, glm::radians(m_rotation), glm::vec3{0.0F, 0.0F, 1.0F}));

    return m_view;
}

auto camera::projection() -> const glm::mat4 & {
    return m_projection;
}

auto camera::position() -> glm::vec3 & {
    return m_position;
}

auto camera::rotation() -> float & {
    return m_rotation;
}
} // namespace phansar::client::graphics
