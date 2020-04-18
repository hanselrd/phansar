#ifndef LIBCOMMON_ALLOCATORS_INCLUDE_COMMON_ALLOCATORS_DEFAULT_ALLOCATOR_HPP
#define LIBCOMMON_ALLOCATORS_INCLUDE_COMMON_ALLOCATORS_DEFAULT_ALLOCATOR_HPP

#include <cstdint>

namespace common::allocators {
template <class T>
class default_allocator {
public:
    using value_type = T;

    default_allocator() = default;
    template <class U>
    explicit default_allocator(const default_allocator<U> & /*unused*/);
    [[nodiscard]] auto allocate(std::size_t nelems) const -> T *;
    void               deallocate(T * ptr, std::size_t nelems) const;
};

template <class T, class U>
auto operator==(const default_allocator<T> & /*unused*/, const default_allocator<U> & /*unused*/)
    -> bool;
template <class T, class U>
auto operator!=(const default_allocator<T> & /*unused*/, const default_allocator<U> & /*unused*/)
    -> bool;
} // namespace common::allocators

#include "../common_allocators_default_allocator.tpp"

#endif