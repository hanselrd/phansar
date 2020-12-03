#include <phansar/client/graphics/vertex.hpp>

namespace phansar::client::graphics {
const bgfx::VertexLayout vertex::k_layout = []() {
    auto layout = bgfx::VertexLayout{};
    layout.begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float)
        /* .add(bgfx::Attrib::Tangent, 3, bgfx::AttribType::Float) */
        /* .add(bgfx::Attrib::Bitangent, 3, bgfx::AttribType::Float) */
        .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
        .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
        .end();
    return layout;
}();
} // namespace phansar::client::graphics
