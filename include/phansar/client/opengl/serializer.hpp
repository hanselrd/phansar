#ifndef PHANSAR_CLENT_OPENGL_CONVERTER_HPP
#define PHANSAR_CLENT_OPENGL_CONVERTER_HPP

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
    static serializer_data serialize(const GLbyte & value) {
        return {GL_BYTE, sizeof(GLbyte), 1, &value};
    }
};

template <>
struct serializer<GLubyte> {
    static serializer_data serialize(const GLubyte & value) {
        return {GL_UNSIGNED_BYTE, sizeof(GLubyte), 1, &value};
    }
};

template <>
struct serializer<GLshort> {
    static serializer_data serialize(const GLshort & value) {
        return {GL_SHORT, sizeof(GLshort), 1, &value};
    }
};

template <>
struct serializer<GLushort> {
    static serializer_data serialize(const GLushort & value) {
        return {GL_UNSIGNED_SHORT, sizeof(GLushort), 1, &value};
    }
};

template <>
struct serializer<GLint> {
    static serializer_data serialize(const GLint & value) {
        return {GL_INT, sizeof(GLint), 1, &value};
    }
};

template <>
struct serializer<GLuint> {
    static serializer_data serialize(const GLuint & value) {
        return {GL_UNSIGNED_INT, sizeof(GLuint), 1, &value};
    }
};

template <>
struct serializer<GLfloat> {
    static serializer_data serialize(const GLfloat & value) {
        return {GL_FLOAT, sizeof(GLfloat), 1, &value};
    }
};

template <>
struct serializer<GLdouble> {
    static serializer_data serialize(const GLdouble & value) {
        return {GL_DOUBLE, sizeof(GLdouble), 1, &value};
    }
};

template <class T, std::size_t N>
struct serializer<T[N]> {
    static_assert(detail::has_serializer<T>::value, "T has no serializer");

    static serializer_data serialize(const T (&value)[N]) {
        auto sa  = serializer<T>::serialize(value[0]);
        sa.count = N;
        return sa;
    }
};

template <class T, std::size_t N>
struct serializer<std::array<T, N>> {
    static_assert(detail::has_serializer<T>::value, "T has no serializer");

    static serializer_data serialize(const std::array<T, N> & value) {
        auto sa  = serializer<T>::serialize(value.at(0));
        sa.count = N;
        return sa;
    }
};
} // namespace phansar::client::opengl

#endif
