#ifndef PHANSAR_CLIENT_OPENGL_TEXTURE_HPP
#define PHANSAR_CLIENT_OPENGL_TEXTURE_HPP

#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>

namespace phansar::client::opengl {
class texture : public common::utility::noncopyable, public common::utility::nonmovable {
public:
    explicit texture(GLenum _target);
    ~texture() override;

    void bind(GLuint _slot = 0) const;
    void unbind() const;

private:
    GLuint m_id;
    GLenum m_target;
};
} // namespace phansar::client::opengl

#endif
