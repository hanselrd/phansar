#ifndef LIBCOMMON_ALLOCATORS_INCLUDE_COMMON_ALLOCATORS_DEFAULT_HPP
#define LIBCOMMON_ALLOCATORS_INCLUDE_COMMON_ALLOCATORS_DEFAULT_HPP

#include <cstdint>

namespace common::allocators {
template <class T> class default_allocator {
public:
    using value_type = T;

    default_allocator() = default;
    template <class U> default_allocator(const default_allocator<U> & /*unused*/);
    auto allocate(std::size_t nelems) -> T *;
    void deallocate(T *ptr, std::size_t nelems);
};

template <class T, class U>
auto operator==(const default_allocator<T> & /*unused*/, const default_allocator<U> & /*unused*/)
    -> bool;
template <class T, class U>
auto operator!=(const default_allocator<T> & /*unused*/, const default_allocator<U> & /*unused*/)
    -> bool;
} // namespace common::allocators

#include "../common_allocators_default.tpp"

#endif
