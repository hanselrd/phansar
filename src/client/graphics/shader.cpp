#include <phansar/client/graphics/shader.hpp>

#include <fstream>
#include <unordered_map>
#include <vector>

namespace phansar::client::graphics {
struct shader::impl {
    bgfx::ProgramHandle                                  handle;
    std::unordered_map<std::string, bgfx::UniformHandle> uniform_map;
};

shader::shader(std::string_view _vertex_file_path, std::string_view _fragment_file_path)
    : m_impl{bgfx::ProgramHandle{}, std::unordered_map<std::string, bgfx::UniformHandle>{}} {
    auto ifs = std::ifstream{std::string{_vertex_file_path}, std::ios::binary};
    auto vertex_blob =
        std::vector<char>{std::istreambuf_iterator<char>{ifs}, std::istreambuf_iterator<char>{}};
    ifs = std::ifstream{std::string{_fragment_file_path}, std::ios::binary};
    auto fragment_blob =
        std::vector<char>{std::istreambuf_iterator<char>{ifs}, std::istreambuf_iterator<char>{}};

    const auto * vertex_mem =
        bgfx::copy(vertex_blob.data(), static_cast<std::uint32_t>(vertex_blob.size() + 1));
    const auto * fragment_mem =
        bgfx::copy(fragment_blob.data(), static_cast<std::uint32_t>(fragment_blob.size() + 1));
    vertex_mem->data[vertex_mem->size - 1]     = '\0';
    fragment_mem->data[fragment_mem->size - 1] = '\0';

    m_impl->handle =
        bgfx::createProgram(bgfx::createShader(vertex_mem), bgfx::createShader(fragment_mem), true);
}

shader::~shader() {
    if (bgfx::isValid(m_impl->handle)) {
        bgfx::destroy(m_impl->handle);
    }

    for (auto & [name, uniform_handle] : m_impl->uniform_map) {
        if (bgfx::isValid(uniform_handle)) {
            bgfx::destroy(uniform_handle);
        }
    }
}

auto shader::handle() const -> const bgfx::ProgramHandle & {
    return m_impl->handle;
}

auto shader::handle() -> bgfx::ProgramHandle & {
    return const_cast<bgfx::ProgramHandle &>(const_cast<const shader *>(this)->handle());
}

void shader::set(std::string_view _name, std::uint8_t _value, const texture & _texture) {
    if (m_impl->uniform_map.count(std::string{_name}) == 0) {
        m_impl->uniform_map.insert_or_assign(
            std::string{_name},
            bgfx::createUniform(std::string{_name}.c_str(), bgfx::UniformType::Sampler));
    }

    bgfx::setTexture(_value, m_impl->uniform_map.at(std::string{_name}), _texture.handle());
}

void shader::set(std::string_view _name, float _value) {
    if (m_impl->uniform_map.count(std::string{_name}) == 0) {
        m_impl->uniform_map.insert_or_assign(
            std::string{_name},
            bgfx::createUniform(std::string{_name}.c_str(), bgfx::UniformType::Vec4));
    }

    bgfx::setUniform(m_impl->uniform_map.at(std::string{_name}),
                     glm::value_ptr(glm::vec4{_value, 0.0F, 0.0F, 0.0F}));
}

void shader::set(std::string_view _name, const glm::vec2 & _value) {
    if (m_impl->uniform_map.count(std::string{_name}) == 0) {
        m_impl->uniform_map.insert_or_assign(
            std::string{_name},
            bgfx::createUniform(std::string{_name}.c_str(), bgfx::UniformType::Vec4));
    }

    bgfx::setUniform(m_impl->uniform_map.at(std::string{_name}),
                     glm::value_ptr(glm::vec4{_value.x, _value.y, 0.0F, 0.0F}));
}

void shader::set(std::string_view _name, const glm::vec3 & _value) {
    if (m_impl->uniform_map.count(std::string{_name}) == 0) {
        m_impl->uniform_map.insert_or_assign(
            std::string{_name},
            bgfx::createUniform(std::string{_name}.c_str(), bgfx::UniformType::Vec4));
    }

    bgfx::setUniform(m_impl->uniform_map.at(std::string{_name}),
                     glm::value_ptr(glm::vec4{_value.x, _value.y, _value.z, 0.0F}));
}

void shader::set(std::string_view _name, const glm::vec4 & _value) {
    if (m_impl->uniform_map.count(std::string{_name}) == 0) {
        m_impl->uniform_map.insert_or_assign(
            std::string{_name},
            bgfx::createUniform(std::string{_name}.c_str(), bgfx::UniformType::Vec4));
    }

    bgfx::setUniform(m_impl->uniform_map.at(std::string{_name}), glm::value_ptr(_value));
}

void shader::set(std::string_view _name, const glm::mat3 & _value) {
    if (m_impl->uniform_map.count(std::string{_name}) == 0) {
        m_impl->uniform_map.insert_or_assign(
            std::string{_name},
            bgfx::createUniform(std::string{_name}.c_str(), bgfx::UniformType::Mat3));
    }

    bgfx::setUniform(m_impl->uniform_map.at(std::string{_name}), glm::value_ptr(_value));
}

void shader::set(std::string_view _name, const glm::mat4 & _value) {
    if (m_impl->uniform_map.count(std::string{_name}) == 0) {
        m_impl->uniform_map.insert_or_assign(
            std::string{_name},
            bgfx::createUniform(std::string{_name}.c_str(), bgfx::UniformType::Mat4));
    }

    bgfx::setUniform(m_impl->uniform_map.at(std::string{_name}), glm::value_ptr(_value));
}
} // namespace phansar::client::graphics
