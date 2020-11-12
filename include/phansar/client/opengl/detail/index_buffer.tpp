#include <phansar/client/opengl/index_buffer.hpp>
#include <phansar/client/opengl/macros.hpp>

namespace phansar::client::opengl {
template <class T>
index_buffer<T>::index_buffer(std::initializer_list<T> _init)
    : m_count{static_cast<GLsizei>(_init.size())} {
    GL_CALL(glGenBuffers(1, &m_id));
    bind();
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         _init.size() * (GLsizeiptr)sizeof(T),
                         std::cbegin(_init),
                         GL_STATIC_DRAW));
    unbind();
}

template <class T>
index_buffer<T>::~index_buffer() {
    unbind();
    GL_CALL(glDeleteBuffers(1, &m_id));
}

template <class T>
void index_buffer<T>::bind() const {
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
}

template <class T>
void index_buffer<T>::unbind() const {
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

template <class T>
auto index_buffer<T>::count() const -> GLsizei {
    return m_count;
}

template <class T>
auto index_buffer<T>::type() const -> GLenum {
    if constexpr (std::is_same_v<T, GLubyte>) {
        return GL_UNSIGNED_BYTE;
    } else if constexpr (std::is_same_v<T, GLushort>) {
        return GL_UNSIGNED_SHORT;
    } else if constexpr (std::is_same_v<T, GLuint>) {
        return GL_UNSIGNED_INT;
    } else {
        PH_ASSERT(false, "");
    }

    return 0;
}
} // namespace phansar::client::opengl
