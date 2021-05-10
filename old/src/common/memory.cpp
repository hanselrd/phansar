#include <phansar/common/macros.hpp>
#include <phansar/common/memory.hpp>

namespace phansar::common::memory {
auto malloc(std::size_t _num_bytes) -> void * {
    PH_ASSERT(_num_bytes > 0);

    auto * ptr = std::malloc(_num_bytes);
    PH_LOG_TRACE("Allocated {} bytes at {}", _num_bytes, ptr);
    return ptr;
}

auto malloc0(std::size_t _num_bytes) -> void * {
    PH_ASSERT(_num_bytes > 0);

    auto * ptr = std::calloc(1, _num_bytes);
    PH_LOG_TRACE("Allocated {} bytes at {} to zero", _num_bytes, ptr);
    return ptr;
}

auto calloc(std::size_t _num, std::size_t _num_bytes) -> void * {
    PH_ASSERT(_num > 0);
    PH_ASSERT(_num_bytes > 0);

    auto * ptr = std::calloc(_num, _num_bytes);
    PH_LOG_TRACE("Allocated {} chunks of {} bytes at {} to zero", _num, _num_bytes, ptr);
    return ptr;
}

auto realloc(void * _ptr, std::size_t _num_bytes) -> void * {
    PH_ASSERT(_ptr != nullptr);
    PH_ASSERT(_num_bytes > 0);

    auto * new_ptr = std::realloc(_ptr, _num_bytes);
    PH_LOG_TRACE("Reallocated {} bytes at {} from {}", _num_bytes, new_ptr, _ptr);
    return new_ptr;
}

void free(void * _ptr) {
    // NOLINTNEXTLINE(clang-analyzer-unix.Malloc)
    PH_ASSERT(_ptr != nullptr);

    // NOLINTNEXTLINE(clang-analyzer-unix.Malloc)
    std::free(_ptr);
    PH_LOG_TRACE("Freed {}", _ptr);
}
} // namespace phansar::common::memory
