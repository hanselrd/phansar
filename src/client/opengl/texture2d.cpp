#include <phansar/client/opengl/texture2d.hpp>

namespace phansar::client::opengl {
texture2d::texture2d(GLint          _level,
                     GLint          _internal_format,
                     GLsizei        _width,
                     GLsizei        _height,
                     GLenum         _format,
                     GLenum         _type,
                     const GLvoid * _data)
    : texture{GL_TEXTURE_2D, _level, _internal_format, _width, _height, 0, _format, _type, _data} {}

texture2d::texture2d(const graphics::image & _image)
    : texture2d{0,
                (_image.channels() == 4)   ? GL_RGBA8
                : (_image.channels() == 3) ? GL_RGB8
                : (_image.channels() == 2) ? GL_RG8
                : (_image.channels() == 1) ? GL_R8
                                           : GLint{0},
                static_cast<GLsizei>(_image.width()),
                static_cast<GLsizei>(_image.height()),
                (_image.channels() == 4)   ? GL_RGBA
                : (_image.channels() == 3) ? GL_RGB
                : (_image.channels() == 2) ? GL_RG
                : (_image.channels() == 1) ? GL_RED
                                           : GLenum{0},
                GL_UNSIGNED_BYTE,
                _image.data()} {}
} // namespace phansar::client::opengl
