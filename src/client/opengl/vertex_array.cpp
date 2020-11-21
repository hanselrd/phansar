#include <phansar/client/opengl/vertex_array.hpp>

namespace phansar::client::opengl {
vertex_array::vertex_array(vertex_buffer & _vb, index_buffer & _ib) : m_vb{&_vb}, m_ib{&_ib} {
    glGenVertexArrays(1, &m_id);
    glBindVertexArray(m_id);
    m_vb->bind();
    m_ib->bind();
}

vertex_array::~vertex_array() {
    glDeleteVertexArrays(1, &m_id);
}

void vertex_array::bind() const {
    glBindVertexArray(m_id);
}

void vertex_array::unbind() const {
    glBindVertexArray(0);
}

void vertex_array::pop_attribute() {
    if (m_attrib_count != 0) {
        --m_attrib_count;

        glDisableVertexAttribArray(m_attrib_count);
    }
}

void vertex_array::clear_attributes() {
    while (m_attrib_count != 0) {
        pop_attribute();
    }
}

auto vertex_array::vertices() -> vertex_buffer & {
    return *m_vb;
}

auto vertex_array::indices() -> index_buffer & {
    return *m_ib;
}
} // namespace phansar::client::opengl
