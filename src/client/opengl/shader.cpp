#include <phansar/client/opengl/shader.hpp>
#include <phansar/common/macros.hpp>

namespace phansar::client::opengl {
shader::shader(std::string_view _file_path) {
    m_id = glCreateProgram();

    auto vertex_shader_id   = GLuint{0};
    auto geometry_shader_id = GLuint{0};
    auto fragment_shader_id = GLuint{0};

    auto source_map = parse(_file_path);
    if (source_map.count("vertex") > 0) {
        vertex_shader_id = compile(GL_VERTEX_SHADER, source_map.at("vertex"));
        glAttachShader(m_id, vertex_shader_id);
    }
    if (source_map.count("geometry") > 0) {
        geometry_shader_id = compile(GL_GEOMETRY_SHADER, source_map.at("geometry"));
        glAttachShader(m_id, geometry_shader_id);
    }
    if (source_map.count("fragment") > 0) {
        fragment_shader_id = compile(GL_FRAGMENT_SHADER, source_map.at("fragment"));
        glAttachShader(m_id, fragment_shader_id);
    }

    glLinkProgram(m_id);

    auto result = GLint{};
    glGetProgramiv(m_id, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        auto length = GLint{};
        glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &length);
        auto message = std::vector<GLchar>(static_cast<std::size_t>(length));
        glGetProgramInfoLog(m_id, length, &length, message.data());
        PH_LOG_ERROR("Failed to link shader program: {}", message | ranges::to<std::string>());
        glDeleteProgram(m_id);

        if (source_map.count("vertex") > 0) {
            glDetachShader(m_id, vertex_shader_id);
            glDeleteShader(vertex_shader_id);
        }
        if (source_map.count("geometry") > 0) {
            glDetachShader(m_id, geometry_shader_id);
            glDeleteShader(geometry_shader_id);
        }
        if (source_map.count("fragment") > 0) {
            glDetachShader(m_id, fragment_shader_id);
            glDeleteShader(fragment_shader_id);
        }

        return;
    }

    glValidateProgram(m_id);

    result = GLint{};
    glGetProgramiv(m_id, GL_VALIDATE_STATUS, &result);
    if (result == GL_FALSE) {
        auto length = GLint{};
        glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &length);
        auto message = std::vector<GLchar>(static_cast<std::size_t>(length));
        glGetProgramInfoLog(m_id, length, &length, message.data());
        PH_LOG_ERROR("Failed to validate shader program: {}", message | ranges::to<std::string>());
        glDeleteProgram(m_id);

        if (source_map.count("vertex") > 0) {
            glDetachShader(m_id, vertex_shader_id);
            glDeleteShader(vertex_shader_id);
        }
        if (source_map.count("geometry") > 0) {
            glDetachShader(m_id, geometry_shader_id);
            glDeleteShader(geometry_shader_id);
        }
        if (source_map.count("fragment") > 0) {
            glDetachShader(m_id, fragment_shader_id);
            glDeleteShader(fragment_shader_id);
        }

        return;
    }

    if (source_map.count("vertex") > 0) {
        glDetachShader(m_id, vertex_shader_id);
        glDeleteShader(vertex_shader_id);
    }
    if (source_map.count("geometry") > 0) {
        glDetachShader(m_id, geometry_shader_id);
        glDeleteShader(geometry_shader_id);
    }
    if (source_map.count("fragment") > 0) {
        glDetachShader(m_id, fragment_shader_id);
        glDeleteShader(fragment_shader_id);
    }
}

shader::~shader() {
    unbind();
    glDeleteProgram(m_id);
}

void shader::bind() const {
    glUseProgram(m_id);
}

void shader::unbind() const {
    glUseProgram(0);
}

auto shader::parse(std::string_view _file_path) -> std::unordered_map<std::string, std::string> {
    auto ifs = std::ifstream{std::string{_file_path}};
    auto source =
        std::string{std::istreambuf_iterator<char>{ifs}, std::istreambuf_iterator<char>{}};
    auto source_map     = std::unordered_map<std::string, std::string>{{"__common", ""}};
    auto source_map_itr = source_map.find("__common");

    auto pragma_shader_regex =
        std::regex{R"regex(#\s*pragma\s+shader\s*\(\s*(vertex|geometry|fragment)\s*\))regex"};
    auto end = std::sregex_token_iterator{};
    for (auto itr = std::sregex_token_iterator{std::cbegin(source),
                                               std::cend(source),
                                               pragma_shader_regex,
                                               {-1, 1}};
         itr != end;
         ++itr) {
        if ((*itr == "vertex") || (*itr == "geometry") || (*itr == "fragment")) {
            if (source_map.count(*itr) == 0) {
                source_map.insert_or_assign(*itr, source_map.at("__common"));
            }
            source_map_itr = source_map.find(*itr);
            continue;
        }

        source_map_itr->second += *itr;
    }

    return source_map;
}

auto shader::compile(GLenum _type, std::string_view _source) -> GLuint {
    auto         shader_id = glCreateShader(_type);
    auto         str       = std::string{_source};
    const auto * cstr      = str.c_str();
    glShaderSource(shader_id, 1, &cstr, nullptr);
    glCompileShader(shader_id);

    auto result = GLint{};
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        auto length = GLint{};
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
        auto message = std::vector<GLchar>(static_cast<std::size_t>(length));
        glGetShaderInfoLog(shader_id, length, &length, message.data());
        PH_LOG_ERROR("Failed to compile shader ({:#0{}x}): {}",
                     _type,
                     sizeof(GLenum) + 2,
                     message | ranges::to<std::string>());
        glDeleteShader(shader_id);

        return 0;
    }

    return shader_id;
}
} // namespace phansar::client::opengl
