#ifndef PHANSAR_CLIENT_GRAPHICS_VERTEX_HPP
#define PHANSAR_CLIENT_GRAPHICS_VERTEX_HPP

namespace phansar::client::graphics {
struct vertex {
    glm::vec3 position;
    glm::vec3 normal;
    /* glm::vec3 tangent; */
    /* glm::vec3 bitangent; */
    std::uint32_t color0;
    glm::vec2     texcoord0;

    static const bgfx::VertexLayout k_layout;
};
} // namespace phansar::client::graphics

#endif
