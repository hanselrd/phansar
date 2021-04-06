#ifndef PHANSAR_COMMON_HELPERS_HPP
#define PHANSAR_COMMON_HELPERS_HPP

namespace phansar::common::helpers {
template <class... Ts>
// NOLINTNEXTLINE(readability-identifier-naming)
inline constexpr auto false_v = bool{false};

namespace _ {
template <class F>
class y_combinator_result {
public:
    explicit y_combinator_result(F && _f);

    template <class... Args>
    decltype(auto) operator()(Args &&... _args) const;

private:
    F m_f;
};
} // namespace _

template <class F>
auto y_combinator(F && _f) -> _::y_combinator_result<std::decay_t<F>>;
} // namespace phansar::common::helpers

#include <phansar/common/helpers.inl>

#endif
