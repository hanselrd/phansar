#include "common_allocators_default.hpp"
#include "common_macros.hpp"
#include "common_memory.hpp"

namespace common::allocators {
template <class T>
template <class U>
default_allocator<T>::default_allocator(const default_allocator<U> &) {
}

template <class T> T *default_allocator<T>::allocate(std::size_t nelems) {
    return static_cast<T *>(memory::malloc(nelems * sizeof(T)));
}

template <class T> void default_allocator<T>::deallocate(T *ptr, std::size_t nelems) {
    UNUSED_ARG(nelems);

    memory::free(ptr);
}

template <class T, class U>
bool operator==(const default_allocator<T> &, const default_allocator<U> &) {
    return true;
}

template <class T, class U>
bool operator!=(const default_allocator<T> &, const default_allocator<U> &) {
    return false;
}
} // namespace common::allocators
