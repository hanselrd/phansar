#ifndef PHANSAR_CLIENT_GRAPHICS_SHADER_HPP
#define PHANSAR_CLIENT_GRAPHICS_SHADER_HPP

#include <phansar/client/graphics/texture.hpp>
#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>

namespace phansar::client::graphics {
class shader : public common::utility::noncopyable, public common::utility::nonmovable {
public:
    shader(std::string_view _vertex_file_path, std::string_view _fragment_file_path);
    ~shader() override;

    [[nodiscard]] auto handle() const -> const bgfx::ProgramHandle &;
    auto               handle() -> bgfx::ProgramHandle &;
    void               set(std::string_view _name, std::uint8_t _value, const texture & _texture);
    void               set(std::string_view _name, float _value);
    void               set(std::string_view _name, const glm::vec2 & _value);
    void               set(std::string_view _name, const glm::vec3 & _value);
    void               set(std::string_view _name, const glm::vec4 & _value);
    void               set(std::string_view _name, const glm::mat3 & _value);
    void               set(std::string_view _name, const glm::mat4 & _value);

private:
    bgfx::ProgramHandle                                  m_handle;
    std::unordered_map<std::string, bgfx::UniformHandle> m_uniform_map;
};
} // namespace phansar::client::graphics

#endif
