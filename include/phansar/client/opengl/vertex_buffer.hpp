#ifndef PHANSAR_CLIENT_OPENGL_VERTEX_BUFFER_HPP
#define PHANSAR_CLIENT_OPENGL_VERTEX_BUFFER_HPP

#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>

namespace phansar::client::opengl {
template <class T>
class vertex_buffer : public common::utility::noncopyable, public common::utility::nonmovable {
    static_assert(std::is_standard_layout_v<T>, "T must be standard layout");

public:
    vertex_buffer(std::initializer_list<T> _init);
    ~vertex_buffer() override;

    void bind() const;
    void unbind() const;

private:
    GLuint m_id = 0;
};
} // namespace phansar::client::opengl

#include <phansar/client/opengl/detail/vertex_buffer.tpp>

#endif
