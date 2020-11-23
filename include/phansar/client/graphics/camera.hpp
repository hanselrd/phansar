#ifndef PHANSAR_CLIENT_GRAPHICS_CAMERA_HPP
#define PHANSAR_CLIENT_GRAPHICS_CAMERA_HPP

namespace phansar::client::graphics {
class camera {
public:
    explicit camera(const glm::mat4 & _projection,
                    const glm::vec3 & _position = glm::vec3{},
                    float             _rotation = 0.0F,
                    float             _zoom     = 1.0F);

    auto view() -> const glm::mat4 &;
    auto projection() -> const glm::mat4 &;
    auto position() -> glm::vec3 &;
    auto rotation() -> float &;
    auto zoom() -> float &;

private:
    glm::mat4 m_view;
    glm::mat4 m_projection;
    glm::vec3 m_position;
    float     m_rotation;
    float     m_zoom;
};
} // namespace phansar::client::graphics

#endif
