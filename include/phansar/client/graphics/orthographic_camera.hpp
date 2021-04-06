#ifndef PHANSAR_CLIENT_GRAPHICS_ORTHOGRAPHIC_CAMERA_HPP
#define PHANSAR_CLIENT_GRAPHICS_ORTHOGRAPHIC_CAMERA_HPP

#include <phansar/client/graphics/camera.hpp>
#include <phansar/common/utility/pimpl.hpp>

namespace phansar::client::graphics {
class orthographic_camera : public camera {
public:
    orthographic_camera(float             _left,
                        float             _right,
                        float             _bottom,
                        float             _top,
                        float             _near      = -1.0F,
                        float             _far       = 1.0F,
                        const glm::vec3 & _position  = glm::vec3{},
                        const glm::vec3 & _direction = glm::vec3{0.0F, 0.0F, -1.0F},
                        const glm::vec3 & _up        = glm::vec3{0.0F, 1.0F, 0.0F},
                        const glm::vec3 & _rotation  = glm::vec3{},
                        const glm::vec3 & _scale     = glm::vec3{1.0F});
    orthographic_camera(const orthographic_camera &) = default;
    auto operator=(const orthographic_camera &) -> orthographic_camera & = default;
    orthographic_camera(orthographic_camera &&)                          = default;
    auto operator=(orthographic_camera &&) -> orthographic_camera & = default;
    ~orthographic_camera();

private:
    struct impl;
    common::utility::pimpl<impl> m_impl;
};
} // namespace phansar::client::graphics

#endif
