#ifndef PHANSAR_CLIENT_OPENGL_VERTEX_ARRAY_HPP
#define PHANSAR_CLIENT_OPENGL_VERTEX_ARRAY_HPP

#include <phansar/client/opengl/index_buffer.hpp>
#include <phansar/client/opengl/vertex_buffer.hpp>
#include <phansar/common/utility/noncopyable.hpp>
#include <phansar/common/utility/nonmovable.hpp>

namespace phansar::client::opengl {
class vertex_array : public common::utility::noncopyable, public common::utility::nonmovable {
public:
    vertex_array(vertex_buffer & _vb, index_buffer & _ib);
    ~vertex_array() override;

    void bind() const;
    void unbind() const;
    template <class T, class U>
    void push_attribute(U T::*_member, bool _normalized = false);
    void pop_attribute();
    void clear_attributes();
    auto vertices() -> vertex_buffer &;
    auto indices() -> index_buffer &;

private:
    GLuint          m_id;
    GLuint          m_attrib_count = 0;
    vertex_buffer * m_vb;
    index_buffer *  m_ib;
};
} // namespace phansar::client::opengl

#include <phansar/client/opengl/vertex_array.tpp>

#endif
