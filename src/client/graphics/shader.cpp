#include <phansar/client/graphics/shader.hpp>

namespace phansar::client::graphics {
shader::shader(std::string_view _vertex_file_path, std::string_view _fragment_file_path) {
    auto ifs = std::ifstream{std::string{_vertex_file_path}, std::ios::binary};
    auto vertex_blob =
        std::vector<char>{std::istreambuf_iterator<char>{ifs}, std::istreambuf_iterator<char>{}};
    ifs = std::ifstream{std::string{_fragment_file_path}, std::ios::binary};
    auto fragment_blob =
        std::vector<char>{std::istreambuf_iterator<char>{ifs}, std::istreambuf_iterator<char>{}};

    const auto * vertex_mem   = bgfx::copy(vertex_blob.data(), vertex_blob.size() + 1);
    const auto * fragment_mem = bgfx::copy(fragment_blob.data(), fragment_blob.size() + 1);
    vertex_mem->data[vertex_mem->size - 1]     = '\0';
    fragment_mem->data[fragment_mem->size - 1] = '\0';

    m_handle =
        bgfx::createProgram(bgfx::createShader(vertex_mem), bgfx::createShader(fragment_mem), true);
}

shader::~shader() {
    bgfx::destroy(m_handle);

    for (auto & [name, uniform] : m_uniform_map) {
        bgfx::destroy(uniform);
    }
}

auto shader::handle() const -> const bgfx::ProgramHandle & {
    return m_handle;
}

auto shader::handle() -> bgfx::ProgramHandle & {
    return const_cast<bgfx::ProgramHandle &>(const_cast<const shader *>(this)->handle());
}

void shader::set(std::string_view _name, std::uint8_t _value, const texture & _texture) {
    if (m_uniform_map.count(std::string{_name}) == 0) {
        m_uniform_map.insert_or_assign(
            std::string{_name},
            bgfx::createUniform(std::string{_name}.c_str(), bgfx::UniformType::Sampler));
    }

    bgfx::setTexture(_value, m_uniform_map.at(std::string{_name}), _texture.handle());
}

void shader::set(std::string_view _name, const glm::vec2 & _value) {
    if (m_uniform_map.count(std::string{_name}) == 0) {
        m_uniform_map.insert_or_assign(
            std::string{_name},
            bgfx::createUniform(std::string{_name}.c_str(), bgfx::UniformType::Vec4));
    }

    bgfx::setUniform(m_uniform_map.at(std::string{_name}),
                     glm::value_ptr(glm::vec4{_value.x, _value.y, 0.0F, 0.0F}));
}

void shader::set(std::string_view _name, const glm::vec3 & _value) {
    if (m_uniform_map.count(std::string{_name}) == 0) {
        m_uniform_map.insert_or_assign(
            std::string{_name},
            bgfx::createUniform(std::string{_name}.c_str(), bgfx::UniformType::Vec4));
    }

    bgfx::setUniform(m_uniform_map.at(std::string{_name}),
                     glm::value_ptr(glm::vec4{_value.x, _value.y, _value.z, 0.0F}));
}

void shader::set(std::string_view _name, const glm::vec4 & _value) {
    if (m_uniform_map.count(std::string{_name}) == 0) {
        m_uniform_map.insert_or_assign(
            std::string{_name},
            bgfx::createUniform(std::string{_name}.c_str(), bgfx::UniformType::Vec4));
    }

    bgfx::setUniform(m_uniform_map.at(std::string{_name}), glm::value_ptr(_value));
}

void shader::set(std::string_view _name, const glm::mat3 & _value) {
    if (m_uniform_map.count(std::string{_name}) == 0) {
        m_uniform_map.insert_or_assign(
            std::string{_name},
            bgfx::createUniform(std::string{_name}.c_str(), bgfx::UniformType::Mat3));
    }

    bgfx::setUniform(m_uniform_map.at(std::string{_name}), glm::value_ptr(_value));
}

void shader::set(std::string_view _name, const glm::mat4 & _value) {
    if (m_uniform_map.count(std::string{_name}) == 0) {
        m_uniform_map.insert_or_assign(
            std::string{_name},
            bgfx::createUniform(std::string{_name}.c_str(), bgfx::UniformType::Mat4));
    }

    bgfx::setUniform(m_uniform_map.at(std::string{_name}), glm::value_ptr(_value));
}
} // namespace phansar::client::graphics
