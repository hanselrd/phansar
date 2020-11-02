#ifndef PHANSAR_COMMON_MEMORY_HPP
#define PHANSAR_COMMON_MEMORY_HPP

#include <cstddef>
#include <cstdint>

namespace phansar::common::memory {
auto malloc(std::size_t _num_bytes) -> void *;
auto malloc0(std::size_t _num_bytes) -> void *;
auto calloc(std::size_t _num, std::size_t _num_bytes) -> void *;
auto realloc(void * _ptr, std::size_t _num_bytes) -> void *;
void free(void * _ptr);
} // namespace phansar::common::memory

#endif
