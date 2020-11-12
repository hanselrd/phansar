#include <phansar/client/opengl/macros.hpp>
#include <phansar/client/opengl/vertex_buffer.hpp>

namespace phansar::client::opengl {
template <class T>
vertex_buffer<T>::vertex_buffer(std::initializer_list<T> _init) {
    GL_CALL(glGenBuffers(1, &m_id));
    bind();
    GL_CALL(glBufferData(GL_ARRAY_BUFFER,
                         _init.size() * sizeof(T),
                         std::cbegin(_init),
                         GL_STATIC_DRAW));
    unbind();
}

template <class T>
vertex_buffer<T>::~vertex_buffer() {
    unbind();
    GL_CALL(glDeleteBuffers(1, &m_id));
}

template <class T>
void vertex_buffer<T>::bind() const {
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_id));
}

template <class T>
void vertex_buffer<T>::unbind() const {
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
} // namespace phansar::client::opengl
