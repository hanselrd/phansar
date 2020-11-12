#include <phansar/client/opengl/macros.hpp>
#include <phansar/client/opengl/vertex_array.hpp>

namespace phansar::client::opengl {
vertex_array::vertex_array() {
    GL_CALL(glGenVertexArrays(1, &m_id));
}

vertex_array::~vertex_array() {
    unbind();
    GL_CALL(glDeleteVertexArrays(1, &m_id));
}

void vertex_array::bind() const {
    GL_CALL(glBindVertexArray(m_id));
}

void vertex_array::unbind() const {
    GL_CALL(glBindVertexArray(0));
}
} // namespace phansar::client::opengl
