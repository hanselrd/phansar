#ifndef PHANSAR_CLIENT_GRAPHICS_VERTEX_HPP
#define PHANSAR_CLIENT_GRAPHICS_VERTEX_HPP

#include <phansar/vendor/bgfx.hpp>
#include <phansar/vendor/glm.hpp>

namespace phansar::client::graphics {
struct vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    glm::vec2 texcoord0;

    static const bgfx::VertexLayout k_layout;
};
} // namespace phansar::client::graphics

#endif
