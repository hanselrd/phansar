#ifndef PHANSAR_CLIENT_OPENGL_TRAITS_HPP
#define PHANSAR_CLIENT_OPENGL_TRAITS_HPP

namespace phansar::client::opengl::traits {
template <GLenum E>
using enum_t = std::conditional_t<
    E == GL_BYTE,
    GLbyte,
    std::conditional_t<
        E == GL_UNSIGNED_BYTE,
        GLubyte,
        std::conditional_t<
            E == GL_SHORT,
            GLshort,
            std::conditional_t<
                E == GL_UNSIGNED_SHORT,
                GLushort,
                std::conditional_t<
                    E == GL_INT,
                    GLint,
                    std::conditional_t<
                        E == GL_UNSIGNED_INT,
                        GLuint,
                        std::conditional_t<
                            E == GL_FLOAT,
                            GLfloat,
                            std::conditional_t<E == GL_DOUBLE, GLdouble, void>>>>>>>>;

template <class T>
// NOLINTNEXTLINE(readability-identifier-naming)
inline constexpr auto enum_v = std::conditional_t<
    std::is_same_v<T, GLbyte>,
    std::integral_constant<GLenum, GL_BYTE>,
    std::conditional_t<
        std::is_same_v<T, GLubyte>,
        std::integral_constant<GLenum, GL_UNSIGNED_BYTE>,
        std::conditional_t<
            std::is_same_v<T, GLshort>,
            std::integral_constant<GLenum, GL_SHORT>,
            std::conditional_t<
                std::is_same_v<T, GLushort>,
                std::integral_constant<GLenum, GL_UNSIGNED_SHORT>,
                std::conditional_t<
                    std::is_same_v<T, GLint>,
                    std::integral_constant<GLenum, GL_INT>,
                    std::conditional_t<
                        std::is_same_v<T, GLuint>,
                        std::integral_constant<GLenum, GL_UNSIGNED_INT>,
                        std::conditional_t<
                            std::is_same_v<T, GLfloat>,
                            std::integral_constant<GLenum, GL_FLOAT>,
                            std::conditional_t<std::is_same_v<T, GLdouble>,
                                               std::integral_constant<GLenum, GL_DOUBLE>,
                                               void>>>>>>>>::value;

template <class T, std::size_t N>
// NOLINTNEXTLINE(readability-identifier-naming)
inline constexpr auto enum_v<T[N]> = enum_v<T>;

template <glm::length_t L, class T, glm::qualifier Q>
// NOLINTNEXTLINE(readability-identifier-naming)
inline constexpr auto enum_v<glm::vec<L, T, Q>> = enum_v<T>;

template <glm::length_t C, glm::length_t R, class T, glm::qualifier Q>
// NOLINTNEXTLINE(readability-identifier-naming)
inline constexpr auto enum_v<glm::mat<C, R, T, Q>> = enum_v<T>;

template <class T>
// NOLINTNEXTLINE(readability-identifier-naming)
inline constexpr auto count_v = std::size_t{1};

template <class T, std::size_t N>
// NOLINTNEXTLINE(readability-identifier-naming)
inline constexpr auto count_v<T[N]> = N;

template <glm::length_t L, class T, glm::qualifier Q>
// NOLINTNEXTLINE(readability-identifier-naming)
inline constexpr auto count_v<glm::vec<L, T, Q>> = L;

template <glm::length_t C, glm::length_t R, class T, glm::qualifier Q>
// NOLINTNEXTLINE(readability-identifier-naming)
inline constexpr auto count_v<glm::mat<C, R, T, Q>> = C * R;

template <GLuint I>
using index_t =
    std::conditional_t<I <= 0xFF, GLubyte, std::conditional_t<I <= 0xFFFF, GLushort, GLuint>>;
} // namespace phansar::client::opengl::traits

#endif
