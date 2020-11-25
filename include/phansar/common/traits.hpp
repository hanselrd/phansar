#ifndef PHANSAR_COMMON_TRAITS_HPP
#define PHANSAR_COMMON_TRAITS_HPP

namespace phansar::common::traits {
template <class... Ts>
// NOLINTNEXTLINE(readability-identifier-naming)
inline constexpr auto false_v = bool{false};
} // namespace phansar::common::traits

#endif
