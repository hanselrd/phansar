#include <phansar/client/opengl/traits.hpp>
#include <phansar/client/opengl/vertex_array.hpp>

namespace phansar::client::opengl {
template <class T, class U>
void vertex_array::push_attribute(U T::*_member, bool _normalized) {
    static_assert(std::is_member_object_pointer_v<decltype(_member)>,
                  "U must be a member object pointer");

    using stripped_U_type =
        std::conditional_t<std::is_array_v<U>, std::remove_pointer_t<std::decay_t<U>>, U>;

    static auto t = T{};

    glEnableVertexAttribArray(m_attrib_count);
    glVertexAttribPointer(
        m_attrib_count,
        sizeof(U) / sizeof(stripped_U_type),
        traits::type_to_enum_v<stripped_U_type>,
        _normalized ? GL_TRUE : GL_FALSE,
        sizeof(T),
        reinterpret_cast<const GLvoid *>(reinterpret_cast<std::uint8_t *>(&(t.*_member)) -
                                         reinterpret_cast<std::uint8_t *>(&t)));

    ++m_attrib_count;
}
} // namespace phansar::client::opengl
