#include <phansar/common/allocators/mallocator.hpp>

#include <cstdlib>

namespace phansar::common::allocators {
template <class T>
template <class U>
mallocator<T>::mallocator(const mallocator<U> & /*unused*/) {}

template <class T>
auto mallocator<T>::allocate(std::size_t _num_elems) const -> T * {
    return static_cast<T *>(std::malloc(_num_elems * sizeof(T)));
}

template <class T>
void mallocator<T>::deallocate(T * _ptr, std::size_t /*unused*/) const {
    std::free(_ptr);
}

template <class T, class U>
auto operator==(const mallocator<T> & /*unused*/, const mallocator<U> & /*unused*/) -> bool {
    return true;
}

template <class T, class U>
auto operator!=(const mallocator<T> & /*unused*/, const mallocator<U> & /*unused*/) -> bool {
    return false;
}
} // namespace phansar::common::allocators
