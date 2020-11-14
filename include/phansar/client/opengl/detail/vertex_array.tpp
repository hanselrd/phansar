#include <phansar/client/opengl/vertex_array.hpp>
#include <phansar/common/macros.hpp>

namespace phansar::client::opengl {
template <class T, std::size_t VertexCount, std::size_t IndexCount>
vertex_array<T, VertexCount, IndexCount>::vertex_array(std::initializer_list<T>          _vertices,
                                                       std::initializer_list<index_type> _indices)
    : m_vertices{_vertices}, m_indices{_indices} {
    glGenVertexArrays(1, &m_vao_id);
    bind();
    glGenBuffers(1, &m_vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
    glBufferData(GL_ARRAY_BUFFER, VertexCount * sizeof(T), nullptr, GL_DYNAMIC_DRAW);
    glGenBuffers(1, &m_ebo_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 IndexCount * sizeof(index_type),
                 nullptr,
                 GL_DYNAMIC_DRAW);
    update();
    unbind();
}

template <class T, std::size_t VertexCount, std::size_t IndexCount>
vertex_array<T, VertexCount, IndexCount>::~vertex_array() {
    glDeleteVertexArrays(1, &m_vao_id);
    glDeleteBuffers(1, &m_vbo_id);
    glDeleteBuffers(1, &m_ebo_id);
}

template <class T, std::size_t VertexCount, std::size_t IndexCount>
void vertex_array<T, VertexCount, IndexCount>::bind() const {
    glBindVertexArray(m_vao_id);
}

template <class T, std::size_t VertexCount, std::size_t IndexCount>
void vertex_array<T, VertexCount, IndexCount>::unbind() const {
    glBindVertexArray(0);
}

template <class T, std::size_t VertexCount, std::size_t IndexCount>
void vertex_array<T, VertexCount, IndexCount>::update() const {
    PH_ASSERT(m_vertices.size() <= VertexCount,
              "vertex buffer size of {} exceeds limit of {}",
              m_vertices.size(),
              VertexCount);
    PH_ASSERT(m_indices.size() <= IndexCount,
              "index buffer size of {} exceeds limit of {}",
              m_indices.size(),
              IndexCount);

    bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(T), m_vertices.data());
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,
                    0,
                    m_indices.size() * sizeof(index_type),
                    m_indices.data());
    unbind();
}

template <class T, std::size_t VertexCount, std::size_t IndexCount>
template <class U>
void vertex_array<T, VertexCount, IndexCount>::push_attribute(U T::*_member, bool _normalized) {
    static_assert(std::is_member_object_pointer_v<decltype(_member)>,
                  "U must be a member object pointer");

    using stripped_U_type =
        std::conditional_t<std::is_array_v<U>, std::remove_pointer_t<std::decay_t<U>>, U>;

    static auto t = T{};

    bind();
    glEnableVertexAttribArray(m_attrib_count);
    glVertexAttribPointer(
        m_attrib_count,
        sizeof(U) / sizeof(stripped_U_type),
        converter::type_to_enum_v<stripped_U_type>,
        _normalized ? GL_TRUE : GL_FALSE,
        sizeof(T),
        reinterpret_cast<const GLvoid *>(reinterpret_cast<std::uint8_t *>(&(t.*_member)) -
                                         reinterpret_cast<std::uint8_t *>(&t)));
    unbind();

    ++m_attrib_count;
}

template <class T, std::size_t VertexCount, std::size_t IndexCount>
void vertex_array<T, VertexCount, IndexCount>::pop_attribute() {
    if (m_attrib_count != 0) {
        --m_attrib_count;

        bind();
        glDisableVertexAttribArray(m_attrib_count);
        unbind();
    }
}

template <class T, std::size_t VertexCount, std::size_t IndexCount>
void vertex_array<T, VertexCount, IndexCount>::clear_attributes() {
    while (m_attrib_count != 0) {
        pop_attribute();
    }
}

template <class T, std::size_t VertexCount, std::size_t IndexCount>
auto vertex_array<T, VertexCount, IndexCount>::type() const -> GLenum {
    return converter::type_to_enum_v<index_type>;
}

template <class T, std::size_t VertexCount, std::size_t IndexCount>
auto vertex_array<T, VertexCount, IndexCount>::vertices() ->
    typename vertex_array<T, VertexCount, IndexCount>::vertex_buffer_type & {
    return m_vertices;
}

template <class T, std::size_t VertexCount, std::size_t IndexCount>
auto vertex_array<T, VertexCount, IndexCount>::indices() ->
    typename vertex_array<T, VertexCount, IndexCount>::index_buffer_type & {
    return m_indices;
}
} // namespace phansar::client::opengl
