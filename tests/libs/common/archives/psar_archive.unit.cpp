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
#include <common/archives/psar_archive.hpp>
#include <fstream>

using namespace common::archives;

TEST_CASE("can create psar archive", "[libs][common][archives][psar_archive]") {
    psar_archive pa;
}

TEST_CASE("can load psar archive", "[libs][common][archives][psar_archive]") {
    std::ifstream ifs("assets.psar", std::ios::binary);
    psar_archive pa;
    auto j = pa.load(ifs);
    REQUIRE(j["maps"].is_null() == false);
    REQUIRE(j["tilesets"].is_null() == false);
}

TEST_CASE("can save psar archive", "[libs][common][archives][psar_archive]") {
    psar_archive pa;
    {
        std::ofstream ofs("test.psar", std::ios::binary);
        pa.save(ofs, {{"testing", true}});
    }
    std::ifstream ifs("test.psar", std::ios::binary);
    auto j = pa.load(ifs);
    REQUIRE(j["testing"].get<bool>() == true);
}
