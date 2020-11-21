#ifndef PHANSAR_CLIENT_OPENGL_BUFFER_HPP
#define PHANSAR_CLIENT_OPENGL_BUFFER_HPP

#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>

namespace phansar::client::opengl {
class buffer : public common::utility::noncopyable, public common::utility::nonmovable {
public:
    buffer(GLenum         _target,
           GLsizeiptr     _size,
           const GLvoid * _data  = nullptr,
           GLenum         _usage = GL_DYNAMIC_DRAW);
    ~buffer() override;

    void               bind() const;
    void               unbind() const;
    void               read(GLintptr _offset, GLsizeiptr _size, GLvoid * _data) const;
    void               write(GLintptr _offset, GLsizeiptr _size, const GLvoid * _data) const;
    [[nodiscard]] auto map(GLenum _access = GL_READ_WRITE) const -> GLvoid *;
    [[nodiscard]] auto map_range(GLintptr   _offset,
                                 GLsizeiptr _size,
                                 GLbitfield _access = GL_MAP_READ_BIT | GL_MAP_WRITE_BIT) const
        -> GLvoid *;
    [[nodiscard]] auto unmap() const -> bool;
    [[nodiscard]] auto size() const -> GLsizeiptr;

private:
    GLuint     m_id;
    GLenum     m_target;
    GLsizeiptr m_size;
};
} // namespace phansar::client::opengl

#endif
