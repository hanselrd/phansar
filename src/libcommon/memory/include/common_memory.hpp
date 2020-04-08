#ifndef LIBCOMMON_MEMORY_INCLUDE_COMMON_MEMORY_HPP
#define LIBCOMMON_MEMORY_INCLUDE_COMMON_MEMORY_HPP

#include <cstdint>
#include <cstdlib>

namespace common::memory {
auto malloc(std::size_t nbytes) -> void *;
auto malloc0(std::size_t nbytes) -> void *;
auto calloc(std::size_t num, std::size_t nbytes) -> void *;
auto realloc(void *mem, std::size_t nbytes) -> void *;
void free(void *mem);
} // namespace common::memory

#endif
