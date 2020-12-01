#include <phansar/client/graphics/perspective_camera.hpp>

namespace phansar::client::graphics {
perspective_camera::perspective_camera(float             _fov,
                                       float             _aspect,
                                       float             _near,
                                       float             _far,
                                       const glm::vec3 & _position,
                                       const glm::vec3 & _center,
                                       const glm::vec3 & _up,
                                       const glm::vec3 & _rotation,
                                       const glm::vec3 & _scale)
    : camera{glm::perspective(glm::radians(_fov), _aspect, _near, _far),
             _position,
             _center,
             _up,
             _rotation,
             _scale} {}
} // namespace phansar::client::graphics
