#include <phansar/client/opengl/index_buffer.hpp>
#include <phansar/client/opengl/traits.hpp>

namespace phansar::client::opengl {
index_buffer::index_buffer(GLsizei _count, GLenum _type, const GLvoid * _data)
    : buffer{GL_ELEMENT_ARRAY_BUFFER,
             static_cast<GLsizeiptr>(_count *
                                     ((_type == GL_UNSIGNED_BYTE)
                                          ? sizeof(traits::enum_to_type_t<GL_UNSIGNED_BYTE>)
                                      : (_type == GL_UNSIGNED_SHORT)
                                          ? sizeof(traits::enum_to_type_t<GL_UNSIGNED_SHORT>)
                                          : sizeof(traits::enum_to_type_t<GL_UNSIGNED_INT>))),
             _data},
      m_count{_count}, m_type{_type} {}

auto index_buffer::count() const -> GLsizei {
    return m_count;
}

auto index_buffer::type() const -> GLenum {
    return m_type;
}
} // namespace phansar::client::opengl
