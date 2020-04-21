#ifndef PHANSAR_COMMON_MEMORY_HPP
#define PHANSAR_COMMON_MEMORY_HPP

#include <cstddef>
#include <cstdint>
#include <cstdlib>

namespace phansar::common::memory {
auto malloc(std::size_t nbytes) -> void *;
auto malloc0(std::size_t nbytes) -> void *;
auto calloc(std::size_t num, std::size_t nbytes) -> void *;
auto realloc(void * mem, std::size_t nbytes) -> void *;
void free(void * mem);
} // namespace phansar::common::memory

#endif
