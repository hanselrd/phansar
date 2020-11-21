#ifndef PHANSAR_COMMON_TRAITS_HPP
#define PHANSAR_COMMON_TRAITS_HPP

namespace phansar::common::traits {
template <class... Ts>
// NOLINTNEXTLINE(readability-identifier-naming)
inline constexpr bool false_v = false;
} // namespace phansar::common::traits

#endif
