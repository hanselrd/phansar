#include <phansar/client/opengl/buffer.hpp>

namespace phansar::client::opengl {
buffer::buffer(GLenum _target, GLsizeiptr _size, const GLvoid * _data, GLenum _usage)
    : m_target{_target}, m_size{_size} {
    glBindVertexArray(0);
    glGenBuffers(1, &m_id);
    glBindBuffer(m_target, m_id);
    glBufferData(m_target, _size, _data, _usage);
}

buffer::~buffer() {
    glDeleteBuffers(1, &m_id);
}

void buffer::bind() const {
    glBindBuffer(m_target, m_id);
}

void buffer::unbind() const {
    glBindBuffer(m_target, 0);
}

void buffer::read(GLintptr _offset, GLsizeiptr _size, GLvoid * _data) const {
    glGetBufferSubData(m_target, _offset, _size, _data);
}

void buffer::write(GLintptr _offset, GLsizeiptr _size, const GLvoid * _data) const {
    glBufferSubData(m_target, _offset, _size, _data);
}

auto buffer::map(GLenum _access) const -> GLvoid * {
    return glMapBuffer(m_target, _access);
}

auto buffer::map_range(GLintptr _offset, GLsizeiptr _size, GLbitfield _access) const -> GLvoid * {
    return glMapBufferRange(m_target, _offset, _size, _access);
}

auto buffer::unmap() const -> bool {
    return glUnmapBuffer(m_target) == GL_TRUE;
}

auto buffer::size() const -> GLsizeiptr {
    return m_size;
}
} // namespace phansar::client::opengl
