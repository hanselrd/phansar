#ifndef PHANSAR_CLIENT_GRAPHICS_CAMERA_HPP
#define PHANSAR_CLIENT_GRAPHICS_CAMERA_HPP

#include <phansar/common/utility/pimpl.hpp>
#include <phansar/vendor/glm.hpp>

namespace phansar::client::graphics {
class camera {
public:
    explicit camera(const glm::mat4 & _projection,
                    const glm::vec3 & _position  = glm::vec3{},
                    const glm::vec3 & _direction = glm::vec3{0.0F, 0.0F, -1.0F},
                    const glm::vec3 & _up        = glm::vec3{0.0F, 1.0F, 0.0F},
                    const glm::vec3 & _rotation  = glm::vec3{},
                    const glm::vec3 & _scale     = glm::vec3{1.0F});
    camera(const camera &) = default;
    auto operator=(const camera &) -> camera & = default;
    camera(camera &&)                          = default;
    auto operator=(camera &&) -> camera & = default;
    ~camera();

    auto view() -> const glm::mat4 &;
    auto projection() -> const glm::mat4 &;
    auto position() -> glm::vec3 &;
    auto direction() -> glm::vec3 &;
    auto rotation() -> glm::vec3 &;
    auto scale() -> glm::vec3 &;

private:
    struct impl;
    common::utility::pimpl<impl> m_impl;
};
} // namespace phansar::client::graphics

#endif
