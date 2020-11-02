#include <phansar/common/macros.hpp>
#include <phansar/common/memory.hpp>

#include <cstdlib>

namespace phansar::common::memory {
auto malloc(std::size_t _num_bytes) -> void * {
    ASSERT(_num_bytes > 0);

    auto * ptr = std::malloc(_num_bytes);
    LOG_TRACE("Allocated {} bytes at {}", _num_bytes, ptr);
    return ptr;
}

auto malloc0(std::size_t _num_bytes) -> void * {
    ASSERT(_num_bytes > 0);

    auto * ptr = std::calloc(1, _num_bytes);
    LOG_TRACE("Allocated {} bytes at {} to zero", _num_bytes, ptr);
    return ptr;
}

auto calloc(std::size_t _num, std::size_t _num_bytes) -> void * {
    ASSERT(_num > 0);
    ASSERT(_num_bytes > 0);

    auto * ptr = std::calloc(_num, _num_bytes);
    LOG_TRACE("Allocated {} chunks of {} bytes at {} to zero", _num, _num_bytes, ptr);
    return ptr;
}

auto realloc(void * _ptr, std::size_t _num_bytes) -> void * {
    ASSERT(_ptr != nullptr);
    ASSERT(_num_bytes > 0);

    auto * new_ptr = std::realloc(_ptr, _num_bytes);
    LOG_TRACE("Reallocated {} bytes at {} from {}", _num_bytes, new_ptr, _ptr);
    return new_ptr;
}

void free(void * _ptr) {
    ASSERT(_ptr != nullptr);

    // NOLINTNEXTLINE(clang-analyzer-unix.Malloc)
    std::free(_ptr);
    LOG_TRACE("Freed {}", _ptr);
}
} // namespace phansar::common::memory

/* auto operator new(std::size_t num_bytes) -> void * { */
/*     return phansar::common::memory::malloc(num_bytes); */
/* } */

/* auto operator new[](std::size_t num_bytes) -> void * { */
/*     return operator new(num_bytes); */
/* } */

/* void operator delete(void * ptr) noexcept { */
/*     // NOLINTNEXTLINE(clang-analyzer-unix.Malloc) */
/*     phansar::common::memory::free(ptr); */
/* } */

/* void operator delete(void * ptr, std::size_t) noexcept { */
/*     // NOLINTNEXTLINE(clang-analyzer-unix.Malloc) */
/*     operator delete(ptr); */
/* } */

/* void operator delete[](void * ptr) noexcept { */
/*     // NOLINTNEXTLINE(clang-analyzer-unix.Malloc) */
/*     operator delete(ptr); */
/* } */

/* void operator delete[](void * ptr, std::size_t) noexcept { */
/*     // NOLINTNEXTLINE(clang-analyzer-unix.Malloc) */
/*     operator delete(ptr); */
/* } */
