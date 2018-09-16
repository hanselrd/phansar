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
#include <common/core/dispatch_queue.hpp>

using namespace common::core;

TEST_CASE("can create dispatch queue", "[libs][common][core][dispatch_queue]") {
    dispatch_queue dq;
}

TEST_CASE("can dispatch a job", "[libs][common][core][dispatch_queue]") {
    dispatch_queue dq;

    auto fut = dq.dispatch([] { return 1337; });
    REQUIRE(fut.get() == 1337);
}
