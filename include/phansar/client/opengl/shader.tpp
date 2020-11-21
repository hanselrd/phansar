#include <phansar/client/opengl/shader.hpp>
#include <phansar/common/macros.hpp>
#include <phansar/common/traits.hpp>

namespace phansar::client::opengl {
template <class T>
void shader::uniform(std::string_view _name, const T & _value) {
    auto location = glGetUniformLocation(m_id, std::string{_name}.c_str());

    if constexpr (std::is_same_v<T, GLfloat>) {
        glUniform1f(location, _value);
    } else if constexpr (std::is_same_v<T, GLint>) {
        glUniform1i(location, _value);
    } else if constexpr (std::is_same_v<T, GLuint>) {
        glUniform1ui(location, _value);
    } else {
        static_assert(common::traits::false_v<T>, "Not supported");
    }
}

template <glm::length_t L, class T, glm::qualifier Q>
void shader::uniform(std::string_view _name, const glm::vec<L, T, Q> & _value) {
    auto location = glGetUniformLocation(m_id, std::string{_name}.c_str());

    if constexpr (std::is_same_v<glm::vec<L, T, Q>, glm::vec1>) {
        glUniform1fv(location, 1, glm::value_ptr(_value));
    } else if constexpr (std::is_same_v<glm::vec<L, T, Q>, glm::ivec1>) {
        glUniform1iv(location, 1, glm::value_ptr(_value));
    } else if constexpr (std::is_same_v<glm::vec<L, T, Q>, glm::uvec1>) {
        glUniform1uiv(location, 1, glm::value_ptr(_value));
    } else if constexpr (std::is_same_v<glm::vec<L, T, Q>, glm::vec2>) {
        glUniform2fv(location, 1, glm::value_ptr(_value));
    } else if constexpr (std::is_same_v<glm::vec<L, T, Q>, glm::ivec2>) {
        glUniform2iv(location, 1, glm::value_ptr(_value));
    } else if constexpr (std::is_same_v<glm::vec<L, T, Q>, glm::uvec2>) {
        glUniform2uiv(location, 1, glm::value_ptr(_value));
    } else if constexpr (std::is_same_v<glm::vec<L, T, Q>, glm::vec3>) {
        glUniform3fv(location, 1, glm::value_ptr(_value));
    } else if constexpr (std::is_same_v<glm::vec<L, T, Q>, glm::ivec3>) {
        glUniform3iv(location, 1, glm::value_ptr(_value));
    } else if constexpr (std::is_same_v<glm::vec<L, T, Q>, glm::uvec3>) {
        glUniform3uiv(location, 1, glm::value_ptr(_value));
    } else if constexpr (std::is_same_v<glm::vec<L, T, Q>, glm::vec4>) {
        glUniform4fv(location, 1, glm::value_ptr(_value));
    } else if constexpr (std::is_same_v<glm::vec<L, T, Q>, glm::ivec4>) {
        glUniform4iv(location, 1, glm::value_ptr(_value));
    } else if constexpr (std::is_same_v<glm::vec<L, T, Q>, glm::uvec4>) {
        glUniform4uiv(location, 1, glm::value_ptr(_value));
    } else {
        static_assert(common::traits::false_v<glm::vec<L, T, Q>>, "Not supported");
    }
}

template <glm::length_t C, glm::length_t R, class T, glm::qualifier Q>
void shader::uniform(std::string_view _name, const glm::mat<C, R, T, Q> & _value, bool _transpose) {
    auto location = glGetUniformLocation(m_id, std::string{_name}.c_str());

    if constexpr (std::is_same_v<glm::mat<C, R, T, Q>, glm::mat2>) {
        glUniformMatrix2fv(location, 1, _transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(_value));
    } else if constexpr (std::is_same_v<glm::mat<C, R, T, Q>, glm::mat3>) {
        glUniformMatrix3fv(location, 1, _transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(_value));
    } else if constexpr (std::is_same_v<glm::mat<C, R, T, Q>, glm::mat4>) {
        glUniformMatrix4fv(location, 1, _transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(_value));
    } else if constexpr (std::is_same_v<glm::mat<C, R, T, Q>, glm::mat2x3>) {
        glUniformMatrix2x3fv(location, 1, _transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(_value));
    } else if constexpr (std::is_same_v<glm::mat<C, R, T, Q>, glm::mat3x2>) {
        glUniformMatrix3x2fv(location, 1, _transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(_value));
    } else if constexpr (std::is_same_v<glm::mat<C, R, T, Q>, glm::mat2x4>) {
        glUniformMatrix2x4fv(location, 1, _transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(_value));
    } else if constexpr (std::is_same_v<glm::mat<C, R, T, Q>, glm::mat4x2>) {
        glUniformMatrix4x2fv(location, 1, _transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(_value));
    } else if constexpr (std::is_same_v<glm::mat<C, R, T, Q>, glm::mat3x4>) {
        glUniformMatrix3x4fv(location, 1, _transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(_value));
    } else if constexpr (std::is_same_v<glm::mat<C, R, T, Q>, glm::mat4x3>) {
        glUniformMatrix4x3fv(location, 1, _transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(_value));
    } else {
        static_assert(common::traits::false_v<glm::mat<C, R, T, Q>>, "Not supported");
    }
}
} // namespace phansar::client::opengl
