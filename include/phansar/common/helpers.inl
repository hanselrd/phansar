#include <phansar/common/helpers.hpp>

namespace phansar::common::helpers {
namespace _ {
template <class F>
y_combinator_result<F>::y_combinator_result(F && _f) : m_f{std::forward<F>(_f)} {}

template <class F>
template <class... Args>
decltype(auto) y_combinator_result<F>::operator()(Args &&... _args) const {
    return m_f(std::ref(*this), std::forward<Args>(_args)...);
}
} // namespace _

template <class F>
auto y_combinator(F && _f) -> _::y_combinator_result<std::decay_t<F>> {
    return _::y_combinator_result<std::decay_t<F>>{std::forward<F>(_f)};
}
} // namespace phansar::common::helpers
