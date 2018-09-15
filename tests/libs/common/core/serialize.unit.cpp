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
#include <common/core/serialize.hpp>

using namespace common::core::serialize;

TEST_CASE("can convert between host and network byte order", "[libs][common][core][serialize]") {
    SECTION("using uint16_t") {
        std::uint16_t u16 = 0x1234;
        u16 = hton16(u16);
        u16 = ntoh16(u16);
        REQUIRE(u16 == 0x1234);
    }

    SECTION("using uint32_t") {
        std::uint32_t u32 = 0x12345678;
        u32 = hton32(u32);
        u32 = ntoh32(u32);
        REQUIRE(u32 == 0x12345678);
    }

    SECTION("using uint64_t") {
        std::uint64_t u64 = 0x123456789ABCDEF0;
        u64 = hton64(u64);
        u64 = ntoh64(u64);
        REQUIRE(u64 == 0x123456789ABCDEF0);
    }

    SECTION("using float") {
        float f = 100.f;
        f = htonf(f);
        f = ntohf(f);
        REQUIRE(f == Approx(100.0f));
    }

    SECTION("using double") {
        double d = 100.;
        d = htond(d);
        d = ntohd(d);
        REQUIRE(d == Approx(100.));
    }
}
