#include <phansar/client/opengl/texture.hpp>

namespace phansar::client::opengl {
texture::texture(GLenum _target) : m_target{_target} {
    glGenTextures(1, &m_id);
    glBindTexture(m_target, m_id);
}

texture::~texture() {
    glDeleteTextures(1, &m_id);
}

void texture::bind(GLuint _slot) const {
    glActiveTexture(GL_TEXTURE0 + _slot);
    glBindTexture(m_target, m_id);
}

void texture::unbind() const {
    glBindTexture(m_target, 0);
}
} // namespace phansar::client::opengl
