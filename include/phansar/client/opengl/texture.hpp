#ifndef PHANSAR_CLIENT_OPENGL_TEXTURE_HPP
#define PHANSAR_CLIENT_OPENGL_TEXTURE_HPP

#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>

namespace phansar::client::opengl {
class texture : public common::utility::noncopyable, public common::utility::nonmovable {
public:
    texture(GLenum         _target,
            GLint          _level,
            GLint          _internal_format,
            GLsizei        _width,
            GLsizei        _height,
            GLsizei        _depth,
            GLenum         _format,
            GLenum         _type = GL_UNSIGNED_BYTE,
            const GLvoid * _data = nullptr);
    ~texture() override;

    void               bind(GLuint _slot = 0) const;
    void               unbind() const;
    void               read(GLint _level, GLvoid * _data) const;
    void               write(GLint          _level,
                             GLint          _xoffset,
                             GLint          _yoffset,
                             GLint          _zoffset,
                             GLsizei        _width,
                             GLsizei        _height,
                             GLsizei        _depth,
                             const GLvoid * _data) const;
    [[nodiscard]] auto width() const -> GLsizei;
    [[nodiscard]] auto height() const -> GLsizei;
    [[nodiscard]] auto depth() const -> GLsizei;

private:
    GLuint  m_id;
    GLenum  m_target;
    GLenum  m_format;
    GLenum  m_type;
    GLsizei m_width;
    GLsizei m_height;
    GLsizei m_depth;
};
} // namespace phansar::client::opengl

#endif
