#include <phansar/client/graphics/perspective_camera.hpp>

namespace phansar::client::graphics {
struct perspective_camera::impl {};

perspective_camera::perspective_camera(float             _fov,
                                       float             _aspect,
                                       float             _near,
                                       float             _far,
                                       const glm::vec3 & _position,
                                       const glm::vec3 & _direction,
                                       const glm::vec3 & _up,
                                       const glm::vec3 & _rotation,
                                       const glm::vec3 & _scale)
    : camera{glm::perspective(glm::radians(_fov), _aspect, _near, _far),
             _position,
             _direction,
             _up,
             _rotation,
             _scale} {}

perspective_camera::~perspective_camera() = default;
} // namespace phansar::client::graphics
