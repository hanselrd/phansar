#ifndef PHANSAR_COMMON_REF_HPP
#define PHANSAR_COMMON_REF_HPP

namespace phansar::common {
template <class T>
using ref = std::shared_ptr<T>;

template <class T, class Deleter = std::default_delete<T>>
using xref = std::unique_ptr<T, Deleter>;
} // namespace phansar::common

#endif
