#include <phansar/client/graphics/orthographic_camera.hpp>

namespace phansar::client::graphics {
orthographic_camera::orthographic_camera(float             _left,
                                         float             _right,
                                         float             _bottom,
                                         float             _top,
                                         float             _near,
                                         float             _far,
                                         const glm::vec3 & _position,
                                         const glm::vec3 & _direction,
                                         const glm::vec3 & _up,
                                         const glm::vec3 & _rotation,
                                         const glm::vec3 & _scale)
    : camera{glm::ortho(_left, _right, _bottom, _top, _near, _far),
             _position,
             _direction,
             _up,
             _rotation,
             _scale} {}
} // namespace phansar::client::graphics
