#include <phansar/client/opengl/texture2d.hpp>

namespace phansar::client::opengl {
texture2d::texture2d(std::string_view _file_path) : texture{GL_TEXTURE_2D} {
    int width;
    int height;
    int channels;

    stbi_set_flip_vertically_on_load(1);
    auto * data = stbi_load(std::string{_file_path}.c_str(), &width, &height, &channels, 0);

    auto internalformat = GLint{};
    auto format         = GLenum{};

    switch (channels) {
    case 3:
        internalformat = GL_RGB8;
        format         = GL_RGB;
        break;
    case 4:
        internalformat = GL_RGBA8;
        format         = GL_RGBA;
        break;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 internalformat,
                 static_cast<GLsizei>(width),
                 static_cast<GLsizei>(height),
                 0,
                 format,
                 GL_UNSIGNED_BYTE,
                 data);

    stbi_image_free(data);
}
} // namespace phansar::client::opengl
