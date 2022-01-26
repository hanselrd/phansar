#ifndef PHANSAR_COMMON_META_Y_COMBINATOR_HPP
#define PHANSAR_COMMON_META_Y_COMBINATOR_HPP

#include <functional>
#include <type_traits>

namespace phansar::common::meta {
namespace detail {
template <class T>
class y_combinator {
public:
    explicit y_combinator(T && _f);

    template <class... Args>
    constexpr auto operator()(Args &&... _args) const -> decltype(auto);

private:
    T m_f{};
};
} // namespace detail

template <class T>
constexpr auto make_y_combinator(T && _f) -> detail::y_combinator<std::decay_t<T>>;
} // namespace phansar::common::meta

#include <phansar/common/meta/y_combinator.inl>

#endif
