#ifndef COMMON_ALLOCATORS_POOL_ALLOCATOR_HPP
#define COMMON_ALLOCATORS_POOL_ALLOCATOR_HPP

#include "base.hpp"
#include <cstdint>
#include <memory>
#include <vector>

namespace common {
namespace allocators {
class pool_allocator : public internal::base {
public:
    explicit pool_allocator(std::size_t size);

    void *allocate(std::size_t size) override;
    void deallocate(void *ptr) override;

private:
    std::unique_ptr<std::uint8_t[]> _buffer;
    std::vector<std::pair<std::uint8_t *, std::size_t>> _malloc;
    std::vector<std::pair<std::uint8_t *, std::size_t>> _free;
    const std::size_t _size;
};
} // namespace allocators
} // namespace common

#endif
