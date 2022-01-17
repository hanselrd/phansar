#include <phansar/client/graphics/camera.hpp>

namespace phansar::client::graphics {
struct camera::impl {
    glm::mat4 view;
    glm::mat4 projection;
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;
    glm::vec3 rotation;
    glm::vec3 scale;
};

camera::camera(const glm::mat4 & _projection,
               const glm::vec3 & _position,
               const glm::vec3 & _direction,
               const glm::vec3 & _up,
               const glm::vec3 & _rotation,
               const glm::vec3 & _scale)
    : m_impl{glm::mat4{},
             _projection,
             _position,
             glm::normalize(_direction),
             glm::normalize(_up),
             _rotation,
             _scale} {}

camera::~camera() = default;

auto camera::view() -> const glm::mat4 & {
    m_impl->view = glm::lookAt(m_impl->position, m_impl->position + m_impl->direction, m_impl->up) *
                   glm::rotate(glm::mat4{1.0F},
                               glm::radians(m_impl->rotation.x),
                               glm::vec3{1.0F, 0.0F, 0.0F}) *
                   glm::rotate(glm::mat4{1.0F},
                               glm::radians(m_impl->rotation.y),
                               glm::vec3{0.0F, 1.0F, 0.0F}) *
                   glm::rotate(glm::mat4{1.0F},
                               glm::radians(m_impl->rotation.z),
                               glm::vec3{0.0F, 0.0F, 1.0F}) *
                   glm::scale(glm::mat4{1.0F}, m_impl->scale);

    return m_impl->view;
}

auto camera::projection() -> const glm::mat4 & {
    return m_impl->projection;
}

auto camera::position() -> glm::vec3 & {
    return m_impl->position;
}

auto camera::direction() -> glm::vec3 & {
    return m_impl->direction;
}

auto camera::rotation() -> glm::vec3 & {
    return m_impl->rotation;
}

auto camera::scale() -> glm::vec3 & {
    return m_impl->scale;
}
} // namespace phansar::client::graphics
