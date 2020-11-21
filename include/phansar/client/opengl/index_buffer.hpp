#ifndef PHANSAR_CLIENT_OPENGL_INDEX_BUFFER_HPP
#define PHANSAR_CLIENT_OPENGL_INDEX_BUFFER_HPP

#include <phansar/client/opengl/buffer.hpp>

namespace phansar::client::opengl {
class index_buffer : public buffer {
public:
    explicit index_buffer(GLsizei        _count,
                          GLenum         _type = GL_UNSIGNED_INT,
                          const GLvoid * _data = nullptr);

    [[nodiscard]] auto count() const -> GLsizei;
    [[nodiscard]] auto type() const -> GLenum;

private:
    GLsizei m_count;
    GLenum  m_type;
};
} // namespace phansar::client::opengl

#endif
