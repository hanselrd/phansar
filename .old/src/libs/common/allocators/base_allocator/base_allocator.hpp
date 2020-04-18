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

#ifndef LIBS_COMMON_ALLOCATORS_BASE_ALLOCATOR_BASE_ALLOCATOR_HPP
#define LIBS_COMMON_ALLOCATORS_BASE_ALLOCATOR_BASE_ALLOCATOR_HPP

#include <cstdint>
#include <new>

namespace common {
namespace allocators {
namespace detail {
class base_allocator {
public:
    virtual ~base_allocator() = default;

    virtual void *allocate(std::size_t size) = 0;
    virtual void deallocate(void *ptr) = 0;
};
} // namespace detail
} // namespace allocators
} // namespace common

void *operator new(std::size_t size, common::allocators::detail::base_allocator &b);

#endif