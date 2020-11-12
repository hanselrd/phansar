#ifndef PHANSAR_CLIENT_OPENGL_VERTEX_BUFFER_LAYOUT_HPP
#define PHANSAR_CLIENT_OPENGL_VERTEX_BUFFER_LAYOUT_HPP

namespace phansar::client::opengl {
class vertex_buffer_layout {
public:
    struct element {
        GLenum    type;
        GLint     count;
        GLboolean normalized;
        GLvoid *  offset;
    };

    template <class T>
    void               push(GLint _count, GLboolean _normalized = GL_FALSE);
    [[nodiscard]] auto elements() const -> const std::vector<element> &;
    [[nodiscard]] auto stride() const -> GLsizei;

private:
    std::vector<element> m_elements;
    GLsizeiptr           m_stride = 0;
};
} // namespace phansar::client::opengl

#include <phansar/client/opengl/detail/vertex_buffer_layout.tpp>

#endif
