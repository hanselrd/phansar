#include <phansar/client/opengl/vertex_buffer_layout.hpp>

namespace phansar::client::opengl {
auto vertex_buffer_layout::elements() const -> const std::vector<vertex_buffer_layout::element> & {
    return m_elements;
}

auto vertex_buffer_layout::stride() const -> GLsizei {
    return static_cast<GLsizei>(m_stride);
}
} // namespace phansar::client::opengl
