#ifndef LIBCOMMON_MEMORY_INCLUDE_COMMON_MEMORY_HPP
#define LIBCOMMON_MEMORY_INCLUDE_COMMON_MEMORY_HPP

#include <cstdint>
#include <cstdlib>

namespace common::memory {
void *malloc(std::size_t nbytes);
void *malloc0(std::size_t nbytes);
void *calloc(std::size_t num, std::size_t nbytes);
void *realloc(void *mem, std::size_t nbytes);
void free(void *mem);
} // namespace common::memory

#endif
