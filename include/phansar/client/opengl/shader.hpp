#ifndef PHANSAR_CLIENT_OPENGL_SHADER_HPP
#define PHANSAR_CLIENT_OPENGL_SHADER_HPP

#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>

namespace phansar::client::opengl {
class shader : public common::utility::noncopyable, public common::utility::nonmovable {
public:
    explicit shader(std::string_view _file_path);
    ~shader() override;

    void bind() const;
    void unbind() const;
    template <class T>
    void uniform(std::string_view _name, const T & _value);
    template <glm::length_t L, class T, glm::qualifier Q>
    void uniform(std::string_view _name, const glm::vec<L, T, Q> & _value);
    template <glm::length_t C, glm::length_t R, class T, glm::qualifier Q>
    void
    uniform(std::string_view _name, const glm::mat<C, R, T, Q> & _value, bool _transpose = false);

private:
    auto parse(std::string_view _file_path) -> std::unordered_map<std::string, std::string>;
    auto compile(GLenum _type, std::string_view _source) -> GLuint;

    GLuint m_id = 0;
};
} // namespace phansar::client::opengl

#include <phansar/client/opengl/shader.tpp>

#endif
