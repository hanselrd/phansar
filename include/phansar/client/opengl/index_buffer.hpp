#ifndef PHANSAR_CLIENT_OPENGL_INDEX_BUFFER_HPP
#define PHANSAR_CLIENT_OPENGL_INDEX_BUFFER_HPP

#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>

namespace phansar::client::opengl {
template <class T>
class index_buffer : public common::utility::noncopyable, public common::utility::nonmovable {
    static_assert(std::is_same_v<T, GLubyte> || std::is_same_v<T, GLushort> ||
                      std::is_same_v<T, GLuint>,
                  "T must be GLubyte, GLushort or GLuint");

public:
    index_buffer(std::initializer_list<T> _init);
    ~index_buffer() override;

    void               bind() const;
    void               unbind() const;
    [[nodiscard]] auto count() const -> GLsizei;
    [[nodiscard]] auto type() const -> GLenum;

private:
    GLuint  m_id    = 0;
    GLsizei m_count = 0;
};
} // namespace phansar::client::opengl

#include <phansar/client/opengl/detail/index_buffer.tpp>

#endif
