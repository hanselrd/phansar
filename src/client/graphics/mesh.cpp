#include <phansar/client/graphics/mesh.hpp>

namespace phansar::client::graphics {
mesh::mesh(const std::vector<vertex> & _vertices, const std::vector<std::uint32_t> & _indices) {
    if (! _vertices.empty()) {
        m_vbo_handle = bgfx::createVertexBuffer(
            bgfx::copy(_vertices.data(),
                       static_cast<std::uint32_t>(_vertices.size() * sizeof(vertex))),
            vertex::k_layout);
    }

    if (! _indices.empty()) {
        m_ibo_handle = bgfx::createIndexBuffer(
            bgfx::copy(_indices.data(),
                       static_cast<std::uint32_t>(_indices.size() * sizeof(std::uint32_t))),
            BGFX_BUFFER_INDEX32);
    }
}

mesh::mesh(mesh && _other) noexcept
    : m_vbo_handle{std::exchange(_other.m_vbo_handle, BGFX_INVALID_HANDLE)},
      m_ibo_handle{std::exchange(_other.m_ibo_handle, BGFX_INVALID_HANDLE)} {}

auto mesh::operator=(mesh && _other) noexcept -> mesh & {
    if (this != &_other) {
        if (bgfx::isValid(m_vbo_handle)) {
            bgfx::destroy(m_vbo_handle);
        }

        if (bgfx::isValid(m_ibo_handle)) {
            bgfx::destroy(m_ibo_handle);
        }

        m_vbo_handle = std::exchange(_other.m_vbo_handle, BGFX_INVALID_HANDLE);
        m_ibo_handle = std::exchange(_other.m_ibo_handle, BGFX_INVALID_HANDLE);
    }
    return *this;
}

mesh::~mesh() {
    if (bgfx::isValid(m_vbo_handle)) {
        bgfx::destroy(m_vbo_handle);
    }

    if (bgfx::isValid(m_ibo_handle)) {
        bgfx::destroy(m_ibo_handle);
    }
}

auto mesh::vbo_handle() const -> const bgfx::VertexBufferHandle & {
    return m_vbo_handle;
}

auto mesh::vbo_handle() -> bgfx::VertexBufferHandle & {
    return const_cast<bgfx::VertexBufferHandle &>(const_cast<const mesh *>(this)->vbo_handle());
}

auto mesh::ibo_handle() const -> const bgfx::IndexBufferHandle & {
    return m_ibo_handle;
}

auto mesh::ibo_handle() -> bgfx::IndexBufferHandle & {
    return const_cast<bgfx::IndexBufferHandle &>(const_cast<const mesh *>(this)->ibo_handle());
}
} // namespace phansar::client::graphics
