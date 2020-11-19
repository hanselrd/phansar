#ifndef PHANSAR_CLIENT_OPENGL_SERIALIZER_HPP
#define PHANSAR_CLIENT_OPENGL_SERIALIZER_HPP

namespace phansar::client::opengl {
namespace detail {
template <GLenum E>
struct type_constant : std::integral_constant<GLenum, E> {};

template <class T, std::size_t N = 1>
struct size_constant : std::integral_constant<std::size_t, N * sizeof(T)> {};
} // namespace detail

struct serializer_data {
    GLenum         type;
    std::size_t    size;
    std::size_t    count;
    const GLvoid * ptr;
};

template <class T>
struct serializer {};

namespace detail {
template <class T, class = void>
struct has_serializer : std::false_type {};

template <class T>
struct has_serializer<T,
                      std::void_t<std::enable_if_t<std::is_same_v<decltype(serializer<T>::serialize(
                                                                      std::declval<const T &>())),
                                                                  serializer_data>>>>
    : std::true_type {};
} // namespace detail

template <>
struct serializer<GLbyte> {
    static auto serialize(const GLbyte & _value) -> serializer_data;
};

template <>
struct serializer<GLubyte> {
    static auto serialize(const GLubyte & _value) -> serializer_data;
};

template <>
struct serializer<GLshort> {
    static auto serialize(const GLshort & _value) -> serializer_data;
};

template <>
struct serializer<GLushort> {
    static auto serialize(const GLushort & _value) -> serializer_data;
};

template <>
struct serializer<GLint> {
    static auto serialize(const GLint & _value) -> serializer_data;
};

template <>
struct serializer<GLuint> {
    static auto serialize(const GLuint & _value) -> serializer_data;
};

template <>
struct serializer<GLfloat> {
    static auto serialize(const GLfloat & _value) -> serializer_data;
};

template <>
struct serializer<GLdouble> {
    static auto serialize(const GLdouble & _value) -> serializer_data;
};

template <class T, std::size_t N>
struct serializer<T[N]> {
    static_assert(detail::has_serializer<T>::value, "T has no serializer");

    static auto serialize(const T (&_value)[N]) -> serializer_data;
};

template <class T, std::size_t N>
struct serializer<std::array<T, N>> {
    static_assert(detail::has_serializer<T>::value, "T has no serializer");

    static auto serialize(const std::array<T, N> & _value) -> serializer_data;
};
} // namespace phansar::client::opengl

#include <phansar/client/opengl/serializer.tpp>

#endif
