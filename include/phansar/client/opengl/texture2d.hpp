#ifndef PHANSAR_CLIENT_OPENGL_TEXTURE2D_HPP
#define PHANSAR_CLIENT_OPENGL_TEXTURE2D_HPP

#include <phansar/client/graphics/image.hpp>
#include <phansar/client/opengl/texture.hpp>

namespace phansar::client::opengl {
class texture2d : public texture {
public:
    texture2d(GLint          _level,
              GLint          _internal_format,
              GLsizei        _width,
              GLsizei        _height,
              GLenum         _format,
              GLenum         _type = GL_UNSIGNED_BYTE,
              const GLvoid * _data = nullptr);
    explicit texture2d(const graphics::image & _image);
};
} // namespace phansar::client::opengl

#endif
