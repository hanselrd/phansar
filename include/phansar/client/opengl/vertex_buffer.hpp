#ifndef PHANSAR_CLIENT_OPENGL_VERTEX_BUFFER_HPP
#define PHANSAR_CLIENT_OPENGL_VERTEX_BUFFER_HPP

#include <phansar/client/opengl/buffer.hpp>

namespace phansar::client::opengl {
class vertex_buffer : public buffer {
public:
    explicit vertex_buffer(GLsizeiptr _size, const GLvoid * _data = nullptr);
};
} // namespace phansar::client::opengl

#endif
