#include <phansar/client/opengl/macros.hpp>
#include <phansar/client/opengl/shader.hpp>
#include <phansar/common/macros.hpp>

namespace phansar::client::opengl {
shader::shader(std::string_view _file_path) {
    GL_CALL(m_id = glCreateProgram());

    auto vertex_shader   = GLuint{0};
    auto geometry_shader = GLuint{0};
    auto fragment_shader = GLuint{0};

    auto source_map = parse(_file_path);
    if (source_map.count("vertex") > 0) {
        vertex_shader = compile(GL_VERTEX_SHADER, source_map.at("vertex"));
        GL_CALL(glAttachShader(m_id, vertex_shader));
    }
    if (source_map.count("geometry") > 0) {
        geometry_shader = compile(GL_GEOMETRY_SHADER, source_map.at("geometry"));
        GL_CALL(glAttachShader(m_id, geometry_shader));
    }
    if (source_map.count("fragment") > 0) {
        fragment_shader = compile(GL_FRAGMENT_SHADER, source_map.at("fragment"));
        GL_CALL(glAttachShader(m_id, fragment_shader));
    }

    GL_CALL(glLinkProgram(m_id));
    GL_CALL(glValidateProgram(m_id));

    if (source_map.count("vertex") > 0) {
        GL_CALL(glDetachShader(m_id, vertex_shader));
        GL_CALL(glDeleteShader(vertex_shader));
    }
    if (source_map.count("geometry") > 0) {
        GL_CALL(glDetachShader(m_id, geometry_shader));
        GL_CALL(glDeleteShader(geometry_shader));
    }
    if (source_map.count("fragment") > 0) {
        GL_CALL(glDetachShader(m_id, fragment_shader));
        GL_CALL(glDeleteShader(fragment_shader));
    }
}

shader::~shader() {
    unbind();
    GL_CALL(glDeleteProgram(m_id));
}

void shader::bind() const {
    GL_CALL(glUseProgram(m_id));
}

void shader::unbind() const {
    GL_CALL(glUseProgram(0));
}

auto shader::parse(std::string_view _file_path) -> std::unordered_map<std::string, std::string> {
    auto source_map      = std::unordered_map<std::string, std::string>{};
    auto source_map_iter = source_map.end();
    auto common_source   = std::string{};

    auto stream = std::ifstream{std::string{_file_path}};

    auto line = std::string{};
    while (std::getline(stream, line)) {
        if (auto pound_idx = line.find('#'); pound_idx != std::string::npos) {
            if (auto pragma_idx = line.find("pragma", pound_idx); pragma_idx != std::string::npos) {
                if (auto shader_idx = line.find("shader", pragma_idx);
                    shader_idx != std::string::npos) {
                    if (auto open_paren_idx = line.find('(', shader_idx);
                        open_paren_idx != std::string::npos) {
                        if (auto close_paren_idx = line.find(')', open_paren_idx);
                            close_paren_idx != std::string::npos) {
                            auto key = line.substr(open_paren_idx + 1,
                                                   close_paren_idx - open_paren_idx - 1);
                            if (source_map.count(key) == 0) {
                                source_map.insert_or_assign(key, common_source);
                            }
                            source_map_iter = source_map.find(key);
                            continue;
                        }
                    }
                }
            }
        }

        line += '\n';

        if (source_map_iter == source_map.end()) {
            common_source += line;
        } else {
            source_map_iter->second += line;
        }
    }

    return source_map;
}

auto shader::compile(GLenum _type, std::string_view _source) -> GLuint {
    GL_CALL(auto shader_id = glCreateShader(_type));
    auto         str  = std::string{_source};
    const auto * cstr = str.c_str();
    GL_CALL(glShaderSource(shader_id, 1, &cstr, nullptr));
    GL_CALL(glCompileShader(shader_id));

    auto result = GLint{};
    GL_CALL(glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        auto length = GLint{};
        GL_CALL(glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length));
        auto message = std::vector<GLchar>(static_cast<std::size_t>(length));
        GL_CALL(glGetShaderInfoLog(shader_id, length, &length, message.data()));
        PH_LOG_ERROR("Failed to compile shader_id ({:#0{}x}): {}",
                     _type,
                     sizeof(GLenum) + 2,
                     message | ranges::to<std::string>());
        GL_CALL(glDeleteShader(shader_id));

        return 0;
    }

    return shader_id;
}

auto shader::uniform_location(std::string_view _name) -> GLint {
    auto name_str = std::string{_name};

    if (m_uniform_location_map.count(name_str) > 0) {
        return m_uniform_location_map.at(name_str);
    }

    GL_CALL(auto location = glGetUniformLocation(m_id, name_str.c_str()));
    PH_ASSERT(location != -1, "");
    m_uniform_location_map.insert_or_assign(name_str, location);
    return location;
}
} // namespace phansar::client::opengl
