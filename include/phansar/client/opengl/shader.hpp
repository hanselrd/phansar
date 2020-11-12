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
    template <class... Args>
    void set_uniform(std::string_view _name, Args &&... _args);

private:
    GLuint                                 m_id = 0;
    std::unordered_map<std::string, GLint> m_uniform_location_map;

    auto parse(std::string_view _file_path) -> std::unordered_map<std::string, std::string>;
    auto compile(GLenum _type, std::string_view _source) -> GLuint;
    auto uniform_location(std::string_view _name) -> GLint;
};
} // namespace phansar::client::opengl

#include <phansar/client/opengl/detail/shader.tpp>

#endif
