#ifndef PHANSAR_COMMON_ALLOCATORS_MALLOCATOR_HPP
#define PHANSAR_COMMON_ALLOCATORS_MALLOCATOR_HPP

namespace phansar::common::allocators {
template <class T>
class mallocator {
public:
    using value_type = T;

    mallocator() = default;
    template <class U>
    explicit mallocator(const mallocator<U> & /*unused*/);
    auto allocate(std::size_t _num_elems) const -> T *;
    void deallocate(T * _ptr, std::size_t /*unused*/) const;
};

template <class T, class U>
auto operator==(const mallocator<T> & /*unused*/, const mallocator<U> & /*unused*/) -> bool;
template <class T, class U>
auto operator!=(const mallocator<T> & /*unused*/, const mallocator<U> & /*unused*/) -> bool;
} // namespace phansar::common::allocators

#include <phansar/common/allocators/detail/mallocator.tpp>

#endif
