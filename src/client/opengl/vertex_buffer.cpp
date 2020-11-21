#include <phansar/client/opengl/vertex_buffer.hpp>

namespace phansar::client::opengl {
vertex_buffer::vertex_buffer(GLsizeiptr _size, const GLvoid * _data)
    : buffer{GL_ARRAY_BUFFER, _size, _data} {}
} // namespace phansar::client::opengl
