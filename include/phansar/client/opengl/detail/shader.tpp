#include <phansar/client/opengl/macros.hpp>
#include <phansar/client/opengl/shader.hpp>

namespace phansar::client::opengl {
template <class... Args>
void shader::set_uniform(std::string_view _name, Args &&... _args) {
    static_assert((std::is_arithmetic_v<Args> && ...), "Args must all be arithmetic type");
    static_assert((std::is_same_v<Args, GLfloat> && ...) || (std::is_same_v<Args, GLint> && ...) ||
                      (std::is_same_v<Args, GLuint> && ...),
                  "Args must all be GLfloat, GLint or GLuint");
    static_assert(sizeof...(Args) >= 1 && sizeof...(Args) <= 4, "Args count must be >= 1 and <= 4");

    bind();
    auto location = uniform_location(_name);
    auto data     = {_args...};

    if constexpr (sizeof...(Args) == 1) {
        if constexpr ((std::is_same_v<Args, GLfloat> && ...)) {
            GL_CALL(glUniform1fv(location, 1, std::cbegin(data)));
        } else if constexpr ((std::is_same_v<Args, GLint> && ...)) {
            GL_CALL(glUniform1iv(location, 1, std::cbegin(data)));
        } else if constexpr ((std::is_same_v<Args, GLuint> && ...)) {
            GL_CALL(glUniform1uiv(location, 1, std::cbegin(data)));
        }
    } else if constexpr (sizeof...(Args) == 2) {
        if constexpr ((std::is_same_v<Args, GLfloat> && ...)) {
            GL_CALL(glUniform2fv(location, 1, std::cbegin(data)));
        } else if constexpr ((std::is_same_v<Args, GLint> && ...)) {
            GL_CALL(glUniform2iv(location, 1, std::cbegin(data)));
        } else if constexpr ((std::is_same_v<Args, GLuint> && ...)) {
            GL_CALL(glUniform2uiv(location, 1, std::cbegin(data)));
        }
    } else if constexpr (sizeof...(Args) == 3) {
        if constexpr ((std::is_same_v<Args, GLfloat> && ...)) {
            GL_CALL(glUniform3fv(location, 1, std::cbegin(data)));
        } else if constexpr ((std::is_same_v<Args, GLint> && ...)) {
            GL_CALL(glUniform3iv(location, 1, std::cbegin(data)));
        } else if constexpr ((std::is_same_v<Args, GLuint> && ...)) {
            GL_CALL(glUniform3uiv(location, 1, std::cbegin(data)));
        }
    } else if constexpr (sizeof...(Args) == 4) {
        if constexpr ((std::is_same_v<Args, GLfloat> && ...)) {
            GL_CALL(glUniform4fv(location, 1, std::cbegin(data)));
        } else if constexpr ((std::is_same_v<Args, GLint> && ...)) {
            GL_CALL(glUniform4iv(location, 1, std::cbegin(data)));
        } else if constexpr ((std::is_same_v<Args, GLuint> && ...)) {
            GL_CALL(glUniform4uiv(location, 1, std::cbegin(data)));
        }
    }

    unbind();
}
} // namespace phansar::client::opengl
