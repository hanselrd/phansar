#include <phansar/client/opengl/serializer.hpp>
#include <phansar/client/opengl/traits.hpp>

namespace phansar::client::opengl {
auto serializer<GLbyte>::serialize(const GLbyte & _value) -> serializer_data {
    return {traits::type_to_enum_v<GLbyte>, sizeof(GLbyte), 1, &_value};
}

auto serializer<GLubyte>::serialize(const GLubyte & _value) -> serializer_data {
    return {traits::type_to_enum_v<GLubyte>, sizeof(GLubyte), 1, &_value};
}

auto serializer<GLshort>::serialize(const GLshort & _value) -> serializer_data {
    return {traits::type_to_enum_v<GLshort>, sizeof(GLshort), 1, &_value};
}

auto serializer<GLushort>::serialize(const GLushort & _value) -> serializer_data {
    return {traits::type_to_enum_v<GLushort>, sizeof(GLushort), 1, &_value};
}

auto serializer<GLint>::serialize(const GLint & _value) -> serializer_data {
    return {traits::type_to_enum_v<GLint>, sizeof(GLint), 1, &_value};
}

auto serializer<GLuint>::serialize(const GLuint & _value) -> serializer_data {
    return {traits::type_to_enum_v<GLuint>, sizeof(GLuint), 1, &_value};
}

auto serializer<GLfloat>::serialize(const GLfloat & _value) -> serializer_data {
    return {traits::type_to_enum_v<GLfloat>, sizeof(GLfloat), 1, &_value};
}

auto serializer<GLdouble>::serialize(const GLdouble & _value) -> serializer_data {
    return {traits::type_to_enum_v<GLdouble>, sizeof(GLdouble), 1, &_value};
}

template <class T, std::size_t N>
auto serializer<T[N]>::serialize(const T (&_value)[N]) -> serializer_data {
    auto sa  = serializer<T>::serialize(_value[0]);
    sa.count = N;
    return sa;
}

template <class T, std::size_t N>
auto serializer<std::array<T, N>>::serialize(const std::array<T, N> & _value) -> serializer_data {
    auto sa  = serializer<T>::serialize(_value.at(0));
    sa.count = N;
    return sa;
}
} // namespace phansar::client::opengl
