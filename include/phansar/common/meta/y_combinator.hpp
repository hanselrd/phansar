#ifndef PHANSAR_COMMON_META_Y_COMBINATOR_HPP
#define PHANSAR_COMMON_META_Y_COMBINATOR_HPP

#include <functional>
#include <type_traits>

namespace phansar::common::meta {
namespace detail {
template <class F>
class y_combinator_result {
public:
    explicit y_combinator_result(F && _f);

    template <class... Args>
    constexpr auto operator()(Args &&... _args) const -> decltype(auto);

private:
    F m_f;
};
} // namespace detail

template <class F>
constexpr auto make_y_combinator(F && _f) -> detail::y_combinator_result<std::decay_t<F>>;
} // namespace phansar::common::meta

#include <phansar/common/meta/y_combinator.inl>

#endif
