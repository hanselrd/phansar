#include "pool_allocator.hpp"

namespace common {
namespace allocators {
pool_allocator::pool_allocator(std::size_t size) : _buffer(new std::uint8_t[size]), _size(size) {
    _free.emplace_back(_buffer.get(), _size);
}

void *pool_allocator::allocate(std::size_t size) {
    for (auto it = _free.begin(); it != _free.end(); ++it) {
        if (it->second > size) {
            auto ptr = it->first;
            it->first += size;
            it->second -= size;
            _malloc.emplace_back(ptr, _size);
            return ptr;
        } else if (it->second == size) {
            auto ptr = it->first;
            _free.erase(it);
            _malloc.emplace_back(ptr, _size);
            return ptr;
        }
    }

    return nullptr;
}

void pool_allocator::deallocate(void *ptr) {
    if ((ptr < _buffer.get()) || (ptr >= _buffer.get() + _size)) {
        return;
    }

    for (auto it = _malloc.begin(); it != _malloc.end(); ++it) {
        if (it->first == ptr) {
            _free.push_back(std::move(*it));
            _malloc.erase(it);
            return;
        }
    }
}
} // namespace allocators
} // namespace common
