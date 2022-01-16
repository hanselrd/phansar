#ifndef PHANSAR_COMMON_META_IS_COMPLETE_HPP
#define PHANSAR_COMMON_META_IS_COMPLETE_HPP

#include <type_traits>

namespace phansar::common::meta {
template <class T, class = void>
struct is_complete : std::false_type {};

template <class T>
struct is_complete<T, std::void_t<decltype(sizeof(T))>> : std::true_type {};

template <class T>
// NOLINTNEXTLINE(readability-identifier-naming)
inline constexpr bool is_complete_v = is_complete<T>::value;
} // namespace phansar::common::meta

#endif
