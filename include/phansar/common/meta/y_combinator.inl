#include <phansar/common/meta/y_combinator.hpp>

namespace phansar::common::meta {
namespace detail {
template <class F>
y_combinator<F>::y_combinator(F && _f) : m_f{std::forward<F>(_f)} {}

template <class F>
template <class... Args>
constexpr auto y_combinator<F>::operator()(Args &&... _args) const -> decltype(auto) {
    return m_f(std::ref(*this), std::forward<Args>(_args)...);
}
} // namespace detail

template <class F>
constexpr auto make_y_combinator(F && _f) -> detail::y_combinator<std::decay_t<F>> {
    return {std::forward<F>(_f)};
}
} // namespace phansar::common::meta
