/**
 * This file is part of Phansar.
 *
 * Copyright (C) 2018  Hansel De La Cruz
 *
 * Phansar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Phansar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with Phansar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "pool_allocator.hpp"
#include "../../utils/log/log.hpp"

namespace common {
namespace allocators {
pool_allocator::pool_allocator(std::size_t size) : _buffer{new std::uint8_t[size]{}}, _size{size} {
    _free.emplace_back(_buffer.get(), _size);
}

void *pool_allocator::allocate(std::size_t size) {
    for (auto it = _free.begin(); it != _free.end(); ++it) {
        auto &[ptr, sz] = *it;
        if (sz > size) {
            ptr += size;
            sz -= size;
            _malloc.emplace_back(ptr - size, size);
            return ptr - size;
        } else if (sz == size) {
            _free.erase(it);
            _malloc.emplace_back(ptr, size);
            return ptr;
        }
    }

    LOGE << "Could not allocate " << size << " bytes";
    return nullptr;
}

void pool_allocator::deallocate(void *ptr) {
    if ((ptr < _buffer.get()) || (ptr >= _buffer.get() + _size)) {
        LOGD << ptr << " does not belong to this allocator";
        return;
    }

    for (auto it = _malloc.begin(); it != _malloc.end(); ++it) {
        const auto &[p, sz] = *it;
        if (p == ptr) {
            _free.push_back(std::move(*it));
            _malloc.erase(it);
            return;
        }
    }

    LOGE << "Could not deallocate " << ptr;
}
} // namespace allocators
} // namespace common
