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

#include "json_archive.hpp"
#include <catch2/catch.hpp>
#include <fstream>

using namespace common::archives;

TEST_CASE("can create json archive", "[libs][common][archives][json_archive]") {
    auto ja = json_archive{};
}

TEST_CASE("can load json archive", "[libs][common][archives][json_archive]") {
    auto ifs = std::ifstream{"../assets/maps/test.json"};
    auto ja = json_archive{};
    auto j = ja.load(ifs);
    REQUIRE(j["width"].get<int>() == 20);
    REQUIRE(j["height"].get<int>() == 20);
}

TEST_CASE("can save json archive", "[libs][common][archives][json_archive]") {
    auto ja = json_archive{};
    {
        auto ofs = std::ofstream{"test.json"};
        ja.save(ofs, {{"testing", true}});
    }
    auto ifs = std::ifstream{"test.json"};
    auto j = ja.load(ifs);
    REQUIRE(j["testing"].get<bool>() == true);
}
