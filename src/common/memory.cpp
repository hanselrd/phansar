#include <phansar/common/log.hpp>
#include <phansar/common/macros.hpp>
#include <phansar/common/memory.hpp>

#include <cstdlib>

namespace phansar::common::memory {
auto malloc(std::size_t nbytes) -> void * {
    /* ASSERT(nbytes > 0); */

    auto * ptr = std::malloc(nbytes);
    LOGT("Allocated {} bytes at {}", nbytes, ptr);
    return ptr;
}

auto malloc0(std::size_t nbytes) -> void * {
    /* ASSERT(nbytes > 0); */

    auto * ptr = std::calloc(1, nbytes);
    LOGT("Allocated {} bytes at {} to zero", nbytes, ptr);
    return ptr;
}

auto calloc(std::size_t num, std::size_t nbytes) -> void * {
    /* ASSERT(num > 0); */
    /* ASSERT(nbytes > 0); */

    auto * ptr = std::calloc(num, nbytes);
    LOGT("Allocated {} chunks of {} bytes at {} to zero", num, nbytes, ptr);
    return ptr;
}

auto realloc(void * ptr, std::size_t nbytes) -> void * {
    /* ASSERT(ptr != nullptr); */
    /* ASSERT(nbytes > 0); */

    auto * new_ptr = std::realloc(ptr, nbytes);
    LOGT("Reallocated {} bytes at {} from {}", nbytes, new_ptr, ptr);
    return new_ptr;
}

void free(void * ptr) {
    /* ASSERT(ptr != nullptr); */

    // NOLINTNEXTLINE(clang-analyzer-unix.Malloc)
    std::free(ptr);
    LOGT("Freed {}", ptr);
}
} // namespace phansar::common::memory

auto operator new(std::size_t nbytes) -> void * {
    return phansar::common::memory::malloc(nbytes);
}

auto operator new[](std::size_t nbytes) -> void * {
    return operator new(nbytes);
}

void operator delete(void * ptr) noexcept {
    // NOLINTNEXTLINE(clang-analyzer-unix.Malloc)
    phansar::common::memory::free(ptr);
}

void operator delete(void * ptr, std::size_t /*unused*/) noexcept {
    // NOLINTNEXTLINE(clang-analyzer-unix.Malloc)
    operator delete(ptr);
}

void operator delete[](void * ptr) noexcept {
    // NOLINTNEXTLINE(clang-analyzer-unix.Malloc)
    operator delete(ptr);
}

void operator delete[](void * ptr, std::size_t /*unused*/) noexcept {
    // NOLINTNEXTLINE(clang-analyzer-unix.Malloc)
    operator delete(ptr);
}
