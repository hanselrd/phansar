#include <phansar/client/opengl/traits.hpp>
#include <phansar/client/opengl/vertex_array.hpp>

namespace phansar::client::opengl {
template <class T, class U>
void vertex_array::push_attribute(U T::*_member, bool _normalized) {
    static_assert(std::is_member_object_pointer_v<decltype(_member)>);

    static auto t = T{};

    glEnableVertexAttribArray(m_attrib_count);
    glVertexAttribPointer(
        m_attrib_count,
        traits::count_v<U>,
        traits::enum_v<U>,
        _normalized ? GL_TRUE : GL_FALSE,
        sizeof(T),
        reinterpret_cast<const GLvoid *>(reinterpret_cast<std::uint8_t *>(&(t.*_member)) -
                                         reinterpret_cast<std::uint8_t *>(&t)));

    ++m_attrib_count;
}
} // namespace phansar::client::opengl
