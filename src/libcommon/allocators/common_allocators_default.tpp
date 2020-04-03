#include "common_allocators_default.hpp"
#include "common_log.hpp"
#include "common_macros.hpp"
#include "common_memory.hpp"
#include <typeinfo>

namespace common::allocators {
template <class T>
template <class U>
default_allocator<T>::default_allocator(const default_allocator<U> &) {
}

template <class T> T *default_allocator<T>::allocate(std::size_t nelems) {
    auto ptr = static_cast<T *>(memory::malloc(nelems * sizeof(T)));
    LOGT("Allocated {} `{}' at {}", nelems, typeid(T).name(), static_cast<void *>(ptr));
    return ptr;
}

template <class T> void default_allocator<T>::deallocate(T *ptr, std::size_t nelems) {
    UNUSED_ARG(nelems);

    memory::free(ptr);
    LOGT("Deallocated {} `{}' at {}", nelems, typeid(T).name(), static_cast<void *>(ptr));
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
