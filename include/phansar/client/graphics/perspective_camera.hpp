#ifndef PHANSAR_CLIENT_GRAPHICS_PERSPECTIVE_CAMERA_HPP
#define PHANSAR_CLIENT_GRAPHICS_PERSPECTIVE_CAMERA_HPP

#include <phansar/client/graphics/camera.hpp>
#include <phansar/common/utility/pimpl.hpp>

namespace phansar::client::graphics {
class perspective_camera : public camera {
public:
    perspective_camera(float             _fov,
                       float             _aspect,
                       float             _near      = 0.1F,
                       float             _far       = 1000.0F,
                       const glm::vec3 & _position  = glm::vec3{0.0F, 0.0F, 1.0F},
                       const glm::vec3 & _direction = glm::vec3{0.0F, 0.0F, -1.0F},
                       const glm::vec3 & _up        = glm::vec3{0.0F, 1.0F, 0.0F},
                       const glm::vec3 & _rotation  = glm::vec3{},
                       const glm::vec3 & _scale     = glm::vec3{1.0F});
    perspective_camera(const perspective_camera &) = default;
    auto operator=(const perspective_camera &) -> perspective_camera & = default;
    perspective_camera(perspective_camera &&)                          = default;
    auto operator=(perspective_camera &&) -> perspective_camera & = default;
    ~perspective_camera();

private:
    struct impl;
    common::utility::pimpl<impl> m_impl;
};
} // namespace phansar::client::graphics

#endif
