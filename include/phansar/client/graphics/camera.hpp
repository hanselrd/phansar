#ifndef PHANSAR_CLIENT_GRAPHICS_CAMERA_HPP
#define PHANSAR_CLIENT_GRAPHICS_CAMERA_HPP

namespace phansar::client::graphics {
class camera {
public:
    explicit camera(const glm::mat4 & _projection);

    auto view() -> const glm::mat4 &;
    auto projection() -> const glm::mat4 &;
    auto position() -> glm::vec3 &;
    auto rotation() -> float &;

private:
    glm::mat4 m_view;
    glm::mat4 m_projection;
    glm::vec3 m_position;
    float     m_rotation = 0.0F;
};
} // namespace phansar::client::graphics

#endif
