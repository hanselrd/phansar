#ifndef PHANSAR_COMMON_TYPES_FMT_HPP
#define PHANSAR_COMMON_TYPES_FMT_HPP

#include <phansar/vendor/fmt.hpp>

namespace phansar::common::types::fmt {
template <class T, template <class> class Allocator>
using basic_memory_buffer = ::fmt::basic_memory_buffer<T, ::fmt::inline_buffer_size, Allocator<T>>;

template <template <class> class Allocator>
using memory_buffer = basic_memory_buffer<char, Allocator>;

template <template <class> class Allocator>
using wmemory_buffer = basic_memory_buffer<wchar_t, Allocator>;
} // namespace phansar::common::types::fmt

#endif
