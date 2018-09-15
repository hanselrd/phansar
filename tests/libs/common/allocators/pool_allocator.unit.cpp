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

#include <catch2/catch.hpp>
#include <common/allocators/pool_allocator.hpp>

using namespace common::allocators;

TEST_CASE("can create pool allocator", "[libs][common][allocators][pool_allocator]") {
    pool_allocator pa(512);
}

TEST_CASE("pool allocator can allocate", "[libs][common][allocators][pool_allocator]") {
    pool_allocator pa(sizeof(int) * 2);

    auto p_int1 = new (pa) int(1337);
    REQUIRE(p_int1 != nullptr);
    REQUIRE(*p_int1 == 1337);

    auto p_int2 = new (pa) int(9001);
    REQUIRE(p_int2 != nullptr);
    REQUIRE((p_int2 - p_int1) == 1);
    REQUIRE(*p_int2 == 9001);
}

TEST_CASE("pool allocator can deallocate", "[libs][common][allocators][pool_allocator]") {
    pool_allocator pa(sizeof(int));

    auto p_int1 = new (pa) int(1337);
    REQUIRE(p_int1 != nullptr);
    REQUIRE(*p_int1 == 1337);

    pa.deallocate(p_int1);

    auto p_int2 = new (pa) int(9001);
    REQUIRE(p_int2 != nullptr);
    REQUIRE(p_int1 == p_int2);
    REQUIRE(*p_int2 == 9001);
}
