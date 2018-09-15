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
