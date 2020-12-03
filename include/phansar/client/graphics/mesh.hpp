#ifndef PHANSAR_CLIENT_GRAPHICS_MESH_HPP
#define PHANSAR_CLIENT_GRAPHICS_MESH_HPP

#include <phansar/client/graphics/vertex.hpp>
#include <phansar/common/utility/noncopyable.hpp>

namespace phansar::client::graphics {
class mesh : public common::utility::noncopyable {
public:
    explicit mesh(const std::vector<vertex> &        _vertices,
                  const std::vector<std::uint32_t> & _indices = {});
    mesh(mesh && _other) noexcept;
    auto operator=(mesh && _other) noexcept -> mesh &;
    ~mesh() override;

    [[nodiscard]] auto vbo_handle() const -> const bgfx::VertexBufferHandle &;
    auto               vbo_handle() -> bgfx::VertexBufferHandle &;
    [[nodiscard]] auto ibo_handle() const -> const bgfx::IndexBufferHandle &;
    auto               ibo_handle() -> bgfx::IndexBufferHandle &;

private:
    bgfx::VertexBufferHandle m_vbo_handle{BGFX_INVALID_HANDLE};
    bgfx::IndexBufferHandle  m_ibo_handle{BGFX_INVALID_HANDLE};
};
} // namespace phansar::client::graphics

#endif
