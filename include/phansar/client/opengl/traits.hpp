#ifndef PHANSAR_CLIENT_OPENGL_TRAITS_HPP
#define PHANSAR_CLIENT_OPENGL_TRAITS_HPP

namespace phansar::client::opengl::traits {
namespace detail {
template <GLenum E>
struct enum_to_type {};

template <>
struct enum_to_type<GL_BYTE> {
    using type = GLbyte;
};

template <>
struct enum_to_type<GL_UNSIGNED_BYTE> {
    using type = GLubyte;
};

template <>
struct enum_to_type<GL_SHORT> {
    using type = GLshort;
};

template <>
struct enum_to_type<GL_UNSIGNED_SHORT> {
    using type = GLushort;
};

template <>
struct enum_to_type<GL_INT> {
    using type = GLint;
};

template <>
struct enum_to_type<GL_UNSIGNED_INT> {
    using type = GLuint;
};

template <>
struct enum_to_type<GL_FLOAT> {
    using type = GLfloat;
};

template <>
struct enum_to_type<GL_DOUBLE> {
    using type = GLdouble;
};

template <class T>
struct type_to_enum {};

template <>
struct type_to_enum<GLbyte> : std::integral_constant<GLenum, GL_BYTE> {};

template <>
struct type_to_enum<GLubyte> : std::integral_constant<GLenum, GL_UNSIGNED_BYTE> {};

template <>
struct type_to_enum<GLshort> : std::integral_constant<GLenum, GL_SHORT> {};

template <>
struct type_to_enum<GLushort> : std::integral_constant<GLenum, GL_UNSIGNED_SHORT> {};

template <>
struct type_to_enum<GLint> : std::integral_constant<GLenum, GL_INT> {};

template <>
struct type_to_enum<GLuint> : std::integral_constant<GLenum, GL_UNSIGNED_INT> {};

template <>
struct type_to_enum<GLfloat> : std::integral_constant<GLenum, GL_FLOAT> {};

template <>
struct type_to_enum<GLdouble> : std::integral_constant<GLenum, GL_DOUBLE> {};

template <GLuint I>
struct index_to_type {
    using type =
        std::conditional_t<I <= 0xff, GLubyte, std::conditional_t<I <= 0xffff, GLushort, GLuint>>;
};
} // namespace detail

template <GLenum E>
using enum_to_type_t = typename detail::enum_to_type<E>::type;

template <class T>
// NOLINTNEXTLINE(readability-identifier-naming)
inline constexpr GLenum type_to_enum_v = detail::type_to_enum<T>::value;

template <GLuint I>
using index_to_type_t = typename detail::index_to_type<I>::type;
} // namespace phansar::client::opengl::traits

#endif
