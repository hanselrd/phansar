#include <phansar/client/opengl/texture.hpp>
#include <phansar/common/macros.hpp>

namespace phansar::client::opengl {
texture::texture(GLenum         _target,
                 GLint          _level,
                 GLint          _internal_format,
                 GLsizei        _width,
                 GLsizei        _height,
                 GLsizei        _depth,
                 GLenum         _format,
                 GLenum         _type,
                 const GLvoid * _data)
    : m_target{_target}, m_format{_format}, m_type{_type}, m_width{_width}, m_height{_height},
      m_depth{_depth} {
    PH_ASSERT(_target == GL_TEXTURE_1D || _target == GL_TEXTURE_2D || _target == GL_TEXTURE_3D);
    PH_ASSERT(_level >= 0);
    PH_ASSERT(_internal_format == GL_RGBA8 || _internal_format == GL_RGB8 ||
              _internal_format == GL_RG8 || _internal_format == GL_R8);
    PH_ASSERT_IF(_target == GL_TEXTURE_1D, _width > 0 && _height == 0 && _depth == 0);
    PH_ASSERT_IF(_target == GL_TEXTURE_2D, _width > 0 && _height > 0 && _depth == 0);
    PH_ASSERT_IF(_target == GL_TEXTURE_3D, _width > 0 && _height > 0 && _depth > 0);
    PH_ASSERT_IF(_internal_format == GL_RGBA8, _format == GL_RGBA);
    PH_ASSERT_IF(_internal_format == GL_RGB8, _format == GL_RGB);
    PH_ASSERT_IF(_internal_format == GL_RG8, _format == GL_RG);
    PH_ASSERT_IF(_internal_format == GL_R8, _format == GL_RED);
    PH_ASSERT(_type == GL_UNSIGNED_BYTE || _type == GL_UNSIGNED_SHORT || _type == GL_UNSIGNED_INT);

    glGenTextures(1, &m_id);
    glBindTexture(m_target, m_id);

    switch (m_target) {
    case GL_TEXTURE_1D:
        glTexImage1D(m_target, _level, _internal_format, _width, 0, m_format, m_type, _data);
        break;
    case GL_TEXTURE_2D:
        glTexImage2D(m_target,
                     _level,
                     _internal_format,
                     _width,
                     _height,
                     0,
                     m_format,
                     m_type,
                     _data);
        break;
    case GL_TEXTURE_3D:
        glTexImage3D(m_target,
                     _level,
                     _internal_format,
                     _width,
                     _height,
                     _depth,
                     0,
                     m_format,
                     m_type,
                     _data);
        break;
    default:
        PH_ASSERT(false);
        break;
    }

    glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

texture::~texture() {
    glDeleteTextures(1, &m_id);
}

void texture::bind(GLuint _slot) const {
    glActiveTexture(GL_TEXTURE0 + _slot);
    glBindTexture(m_target, m_id);
}

void texture::unbind() const {
    glBindTexture(m_target, 0);
}

void texture::read(GLint _level, GLvoid * _data) const {
    PH_ASSERT(_level >= 0);
    PH_ASSERT(_data != nullptr);

    glGetTexImage(m_target, _level, m_format, m_type, _data);
}

void texture::write(GLint          _level,
                    GLint          _xoffset,
                    GLint          _yoffset,
                    GLint          _zoffset,
                    GLsizei        _width,
                    GLsizei        _height,
                    GLsizei        _depth,
                    const GLvoid * _data) {
    PH_ASSERT(_level >= 0);
    PH_ASSERT(_xoffset >= 0 && _xoffset <= m_width);
    PH_ASSERT(_yoffset >= 0 && _yoffset <= m_height);
    PH_ASSERT(_zoffset >= 0 && _zoffset <= m_depth);
    PH_ASSERT(_width <= m_width);
    PH_ASSERT(_height <= m_height);
    PH_ASSERT(_depth <= m_depth);
    PH_ASSERT(_data != nullptr);

    switch (m_target) {
    case GL_TEXTURE_1D:
        glTexSubImage1D(m_target, _level, _xoffset, _width, m_format, m_type, _data);
        break;
    case GL_TEXTURE_2D:
        glTexSubImage2D(m_target,
                        _level,
                        _xoffset,
                        _yoffset,
                        _width,
                        _height,
                        m_format,
                        m_type,
                        _data);
        break;
    case GL_TEXTURE_3D:
        glTexSubImage3D(m_target,
                        _level,
                        _xoffset,
                        _yoffset,
                        _zoffset,
                        _width,
                        _height,
                        _depth,
                        m_format,
                        m_type,
                        _data);
        break;
    default:
        PH_ASSERT(false);
        break;
    }
}

auto texture::width() const -> GLsizei {
    return m_width;
}

auto texture::height() const -> GLsizei {
    return m_height;
}

auto texture::depth() const -> GLsizei {
    return m_depth;
}
} // namespace phansar::client::opengl
