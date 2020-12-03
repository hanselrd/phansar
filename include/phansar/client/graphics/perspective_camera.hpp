#ifndef PHANSAR_CLIENT_GRAPHICS_PERSPECTIVE_CAMERA_HPP
#define PHANSAR_CLIENT_GRAPHICS_PERSPECTIVE_CAMERA_HPP

#include <phansar/client/graphics/camera.hpp>

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
};
} // namespace phansar::client::graphics

#endif
