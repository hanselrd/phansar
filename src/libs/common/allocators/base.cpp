#include "base.hpp"
#include "../core/log.hpp"

void *operator new(std::size_t size, common::allocators::internal::base &b) {
    LOGD << "Allocated " << size << " bytes";
    return b.allocate(size);
}
