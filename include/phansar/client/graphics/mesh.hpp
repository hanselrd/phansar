#ifndef PHANSAR_CLIENT_GRAPHICS_MESH_HPP
#define PHANSAR_CLIENT_GRAPHICS_MESH_HPP

#include <phansar/client/graphics/vertex.hpp>
#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/pimpl.hpp>

#include <vector>

namespace phansar::client::graphics {
class mesh : public common::utility::noncopyable {
public:
    explicit mesh(const std::vector<vertex> &        _vertices,
                  const std::vector<std::uint32_t> & _indices = {});
    mesh(const mesh &) = default;
    auto operator=(const mesh &) -> mesh & = default;
    mesh(mesh && _other) noexcept;
    auto operator=(mesh && _other) noexcept -> mesh &;
    ~mesh();

    [[nodiscard]] auto vbo_handle() const -> const bgfx::VertexBufferHandle &;
    auto               vbo_handle() -> bgfx::VertexBufferHandle &;
    [[nodiscard]] auto ibo_handle() const -> const bgfx::IndexBufferHandle &;
    auto               ibo_handle() -> bgfx::IndexBufferHandle &;

private:
    struct impl;
    common::utility::pimpl<impl> m_impl;
};
} // namespace phansar::client::graphics

#endif
