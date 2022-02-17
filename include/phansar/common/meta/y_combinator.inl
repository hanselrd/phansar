#include <phansar/common/meta/y_combinator.hpp>

namespace phansar::common::meta {
namespace detail {
template <class T>
constexpr y_combinator<T>::y_combinator(T && _f) : m_f{std::forward<T>(_f)} {}

template <class T>
template <class... Args>
constexpr auto y_combinator<T>::operator()(Args &&... _args) const -> decltype(auto) {
    return m_f(std::ref(*this), std::forward<Args>(_args)...);
}
} // namespace detail

template <class T>
constexpr auto make_y_combinator(T && _f) -> detail::y_combinator<std::decay_t<T>> {
    return detail::y_combinator{std::forward<T>(_f)};
}
} // namespace phansar::common::meta
