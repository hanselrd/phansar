#ifndef PHANSAR_CLIENT_GRAPHICS_CAMERA_HPP
#define PHANSAR_CLIENT_GRAPHICS_CAMERA_HPP

namespace phansar::client::graphics {
class camera {
public:
    explicit camera(const glm::mat4 & _projection,
                    const glm::vec3 & _position  = glm::vec3{},
                    const glm::vec3 & _direction = glm::vec3{0.0F, 0.0F, -1.0F},
                    const glm::vec3 & _up        = glm::vec3{0.0F, 1.0F, 0.0F},
                    const glm::vec3 & _rotation  = glm::vec3{},
                    const glm::vec3 & _scale     = glm::vec3{1.0F});

    auto view() -> const glm::mat4 &;
    auto projection() -> const glm::mat4 &;
    auto position() -> glm::vec3 &;
    auto direction() -> glm::vec3 &;
    auto rotation() -> glm::vec3 &;
    auto scale() -> glm::vec3 &;

private:
    glm::mat4 m_view;
    glm::mat4 m_projection;
    glm::vec3 m_position;
    glm::vec3 m_direction;
    glm::vec3 m_up;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
};
} // namespace phansar::client::graphics

#endif
