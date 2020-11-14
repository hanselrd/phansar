#ifndef PHANSAR_CLIENT_OPENGL_VERTEX_ARRAY_HPP
#define PHANSAR_CLIENT_OPENGL_VERTEX_ARRAY_HPP

#include <phansar/client/opengl/converter.hpp>
#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>

namespace phansar::client::opengl {
template <class T, std::size_t VertexCount, std::size_t IndexCount>
class vertex_array : public common::utility::noncopyable, public common::utility::nonmovable {
    static_assert(std::is_standard_layout_v<T>, "T must be a standard layout type");

public:
    using index_type         = converter::index_to_type_t<IndexCount>;
    using vertex_buffer_type = std::vector<T>;
    using index_buffer_type  = std::vector<index_type>;

    vertex_array(std::initializer_list<T>          _vertices = {},
                 std::initializer_list<index_type> _indices  = {});
    ~vertex_array() override;

    void bind() const;
    void unbind() const;
    void update() const;
    template <class U>
    void               push_attribute(U T::*_member, bool _normalized = false);
    void               pop_attribute();
    void               clear_attributes();
    [[nodiscard]] auto type() const -> GLenum;
    auto               vertices() -> vertex_buffer_type &;
    auto               indices() -> index_buffer_type &;

private:
    GLuint             m_vao_id       = 0;
    GLuint             m_vbo_id       = 0;
    GLuint             m_ebo_id       = 0;
    GLuint             m_attrib_count = 0;
    vertex_buffer_type m_vertices;
    index_buffer_type  m_indices;
};
} // namespace phansar::client::opengl

#include <phansar/client/opengl/detail/vertex_array.tpp>

#endif
