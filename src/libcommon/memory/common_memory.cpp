#include "common_memory.hpp"
#include "common_log.hpp"
#include "common_macros.hpp"
#include <cstdlib>

namespace common::memory {
auto malloc(std::size_t nbytes) -> void * {
    ASSERT(nbytes > 0);

    auto ptr = std::malloc(nbytes);
    LOGT("Allocated {} bytes at {}", nbytes, ptr);
    return ptr;
}

auto malloc0(std::size_t nbytes) -> void * {
    ASSERT(nbytes > 0);

    auto ptr = std::calloc(1, nbytes);
    LOGT("Allocated {} bytes at {} to zero", nbytes, ptr);
    return ptr;
}

auto calloc(std::size_t num, std::size_t nbytes) -> void * {
    ASSERT(num > 0);
    ASSERT(nbytes > 0);

    auto ptr = std::calloc(num, nbytes);
    LOGT("Allocated {} chunks of {} bytes at {} to zero", num, nbytes, ptr);
    return ptr;
}

auto realloc(void *mem, std::size_t nbytes) -> void * {
    ASSERT(mem != nullptr);
    ASSERT(nbytes > 0);

    auto ptr = std::realloc(mem, nbytes);
    LOGT("Reallocated {} bytes at {} from {}", nbytes, ptr, mem);
    return ptr;
}

void free(void *mem) {
    ASSERT(mem != nullptr);

    std::free(mem);
    LOGT("Freed {}", mem);
}
} // namespace common::memory
