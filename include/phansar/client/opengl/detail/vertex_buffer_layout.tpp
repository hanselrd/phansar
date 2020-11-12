#include <phansar/client/opengl/macros.hpp>
#include <phansar/client/opengl/vertex_buffer_layout.hpp>

namespace phansar::client::opengl {
template <class T>
void vertex_buffer_layout::push(GLint _count, GLboolean _normalized) {
    static_assert(std::is_arithmetic_v<T>, "T must be arithmetic type");

    if constexpr (std::is_same_v<T, GLbyte>) {
        m_elements.push_back({GL_BYTE, _count, _normalized, reinterpret_cast<GLvoid *>(m_stride)});
    } else if constexpr (std::is_same_v<T, GLubyte>) {
        m_elements.push_back(
            {GL_UNSIGNED_BYTE, _count, _normalized, reinterpret_cast<GLvoid *>(m_stride)});
    } else if constexpr (std::is_same_v<T, GLshort>) {
        m_elements.push_back({GL_SHORT, _count, _normalized, reinterpret_cast<GLvoid *>(m_stride)});
    } else if constexpr (std::is_same_v<T, GLushort>) {
        m_elements.push_back(
            {GL_UNSIGNED_SHORT, _count, _normalized, reinterpret_cast<GLvoid *>(m_stride)});
    } else if constexpr (std::is_same_v<T, GLint>) {
        m_elements.push_back({GL_INT, _count, _normalized, reinterpret_cast<GLvoid *>(m_stride)});
    } else if constexpr (std::is_same_v<T, GLuint>) {
        m_elements.push_back(
            {GL_UNSIGNED_INT, _count, _normalized, reinterpret_cast<GLvoid *>(m_stride)});
    } else if constexpr (std::is_same_v<T, GLfloat>) {
        m_elements.push_back({GL_FLOAT, _count, _normalized, reinterpret_cast<GLvoid *>(m_stride)});
    } else if constexpr (std::is_same_v<T, GLdouble>) {
        m_elements.push_back(
            {GL_DOUBLE, _count, _normalized, reinterpret_cast<GLvoid *>(m_stride)});
    } else {
        PH_ASSERT(false, "");
    }

    m_stride += static_cast<GLuint>(_count) * sizeof(T);
}
} // namespace phansar::client::opengl
