#include <phansar/client/graphics/camera.hpp>

namespace phansar::client::graphics {
camera::camera(const glm::mat4 & _projection,
               const glm::vec3 & _position,
               const glm::vec3 & _center,
               const glm::vec3 & _up,
               const glm::vec3 & _rotation,
               const glm::vec3 & _scale)
    : m_projection{_projection}, m_position{_position}, m_center{_center}, m_up{_up},
      m_rotation{_rotation}, m_scale{_scale} {}

auto camera::view() -> const glm::mat4 & {
    m_view = glm::lookAt(m_position, m_position + m_center, m_up) *
             glm::rotate(glm::mat4{1.0F}, glm::radians(m_rotation.x), glm::vec3{1.0F, 0.0F, 0.0F}) *
             glm::rotate(glm::mat4{1.0F}, glm::radians(m_rotation.y), glm::vec3{0.0F, 1.0F, 0.0F}) *
             glm::rotate(glm::mat4{1.0F}, glm::radians(m_rotation.z), glm::vec3{0.0F, 0.0F, 1.0F}) *
             glm::scale(glm::mat4{1.0F}, m_scale);

    return m_view;
}

auto camera::projection() -> const glm::mat4 & {
    return m_projection;
}

auto camera::position() -> glm::vec3 & {
    return m_position;
}

auto camera::rotation() -> glm::vec3 & {
    return m_rotation;
}

auto camera::scale() -> glm::vec3 & {
    return m_scale;
}
} // namespace phansar::client::graphics
