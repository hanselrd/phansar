#ifndef COMMON_ALLOCATORS_BASE_HPP
#define COMMON_ALLOCATORS_BASE_HPP

#include <cstdint>
#include <new>

namespace common {
namespace allocators {
namespace internal {
class base {
public:
    virtual ~base() = default;

    virtual void *allocate(std::size_t size) = 0;
    virtual void deallocate(void *ptr) = 0;
};
} // namespace internal
} // namespace allocators
} // namespace common

void *operator new(std::size_t size, common::allocators::internal::base &b);

#endif
