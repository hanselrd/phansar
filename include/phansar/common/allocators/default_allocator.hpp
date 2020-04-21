#ifndef PHANSAR_COMMON_ALLOCATORS_DEFAULT_ALLOCATOR_HPP
#define PHANSAR_COMMON_ALLOCATORS_DEFAULT_ALLOCATOR_HPP

#include <cstddef>
#include <cstdint>

namespace phansar::common::allocators {
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
} // namespace phansar::common::allocators

#include <phansar/common/allocators/detail/default_allocator.tpp>

#endif
