#include <phansar/client/graphics/orthographic_camera.hpp>

namespace phansar::client::graphics {
orthographic_camera::orthographic_camera(float             _left,
                                         float             _right,
                                         float             _bottom,
                                         float             _top,
                                         float             _near,
                                         float             _far,
                                         const glm::vec3 & _position,
                                         float             _rotation)
    : camera{glm::ortho(_left, _right, _bottom, _top, _near, _far), _position, _rotation} {}
} // namespace phansar::client::graphics
