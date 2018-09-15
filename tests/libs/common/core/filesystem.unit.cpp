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
#include <common/core/filesystem.hpp>

using namespace common::core::filesystem;

TEST_CASE("can open a file", "[libs][common][core][filesystem]") {
    file f("assets.psar");
    REQUIRE(f.exists());
}

TEST_CASE("can open a directory", "[libs][common][core][filesystem]") {
    directory dir("scripts");
    REQUIRE(dir.exists());
    REQUIRE(dir.get_path() == "scripts");
}

TEST_CASE("can see a directory_entry", "[libs][common][core][filesystem]") {
    directory dir("scripts");
    REQUIRE(dir.exists());
    REQUIRE(dir.get_path() == "scripts");

    auto entry = dir.next_entry();
    REQUIRE(
        (entry->get_name() == "." || entry->get_name() == ".." || entry->get_name() == "lua_api"));
    REQUIRE(entry->get_type() == directory_entry::type::DIRECTORY);
}
