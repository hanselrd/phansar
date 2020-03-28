/**
 *  This file is part of Phansar.
 *
 *  Copyright (C) 2019  Hansel De La Cruz
 *
 *  Phansar is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Phansar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with Phansar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "atomic.hpp"
#include <catch2/catch.hpp>
#include <thread>
#include <vector>

using namespace common::utils;

TEST_CASE("can fetch_add atomically", "[libs][common][utils][atomic]") {
    auto threads = std::vector<std::thread>{};
    auto x = std::atomic_uint64_t{0};
    for (auto i = std::uint32_t{0}; i < 4; ++i) {
        threads.push_back(std::thread{[&x] {
            for (auto j = std::uint32_t{0}; j < 1000; ++j) {
                atomic::fetch_add(x, std::uint64_t{1});
            }
        }});
    }

    for (auto &t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    REQUIRE(x.load() == 4000);
}

TEST_CASE("can fetch_sub atomically", "[libs][common][utils][atomic]") {
    auto threads = std::vector<std::thread>{};
    auto x = std::atomic_int64_t{0};
    for (auto i = std::uint32_t{0}; i < 4; ++i) {
        threads.push_back(std::thread{[&x] {
            for (auto j = std::uint32_t{0}; j < 1000; ++j) {
                atomic::fetch_sub(x, std::int64_t{1});
            }
        }});
    }

    for (auto &t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    REQUIRE(x.load() == -4000);
}
