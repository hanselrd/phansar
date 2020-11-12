#ifndef PHANSAR_CLIENT_OPENGL_VERTEX_ARRAY_HPP
#define PHANSAR_CLIENT_OPENGL_VERTEX_ARRAY_HPP

#include <phansar/client/opengl/vertex_buffer.hpp>
#include <phansar/client/opengl/vertex_buffer_layout.hpp>
#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>

namespace phansar::client::opengl {
class vertex_array : public common::utility::noncopyable, public common::utility::nonmovable {
public:
    vertex_array();
    ~vertex_array() override;

    void bind() const;
    void unbind() const;
    template <class T>
    void add_buffer(const vertex_buffer<T> & _vb, const vertex_buffer_layout & _layout) const;

private:
    GLuint m_id = 0;
};
} // namespace phansar::client::opengl

#include <phansar/client/opengl/detail/vertex_array.tpp>

#endif
