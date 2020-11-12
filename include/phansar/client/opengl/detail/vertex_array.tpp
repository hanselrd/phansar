#include <phansar/client/opengl/macros.hpp>
#include <phansar/client/opengl/vertex_array.hpp>

namespace phansar::client::opengl {
template <class T>
void vertex_array::add_buffer(const vertex_buffer<T> &     _vb,
                              const vertex_buffer_layout & _layout) const {
    bind();
    _vb.bind();
    for (auto && [index, e] : _layout.elements() | ranges::views::enumerate) {
        GL_CALL(glEnableVertexAttribArray((GLuint)index));
        GL_CALL(glVertexAttribPointer((GLuint)index,
                                      e.count,
                                      e.type,
                                      e.normalized,
                                      _layout.stride(),
                                      e.offset));
    }
    _vb.unbind();
    unbind();
}
} // namespace phansar::client::opengl
