#ifndef PHANSAR_CLIENT_GRAPHICS_ORTHOGRAPHIC_CAMERA_HPP
#define PHANSAR_CLIENT_GRAPHICS_ORTHOGRAPHIC_CAMERA_HPP

#include <phansar/client/graphics/camera.hpp>

namespace phansar::client::graphics {
class orthographic_camera : public camera {
public:
    orthographic_camera(float             _left,
                        float             _right,
                        float             _bottom,
                        float             _top,
                        float             _near     = -1.0F,
                        float             _far      = 1.0F,
                        const glm::vec3 & _position = glm::vec3{},
                        const glm::vec3 & _center   = glm::vec3{0.0F, 0.0F, -1.0F},
                        const glm::vec3 & _up       = glm::vec3{0.0F, 1.0F, 0.0F},
                        const glm::vec3 & _rotation = glm::vec3{},
                        const glm::vec3 & _scale    = glm::vec3{1.0F});
};
} // namespace phansar::client::graphics

#endif
