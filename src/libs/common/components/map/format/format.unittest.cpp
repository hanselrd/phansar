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

#include "../../../archives/psar_archive/psar_archive.hpp"
#include "map/map.hpp"
#include <catch2/catch.hpp>
#include <fstream>

using namespace common;
using namespace common::components::map_detail;

TEST_CASE("can read map files", "[libs][common][components][map][format]") {
    auto ifs = std::ifstream{"assets.psar", std::ios::binary};
    auto pa = archives::psar_archive{};
    auto j = pa.load(ifs);

    const auto map = j["maps"]["test.json"].get<format::_map_>();
    REQUIRE(map.height == 20);
    REQUIRE(map.infinite == false);
    REQUIRE(map.layers.size() == 3);
    const auto map_layer0 = map.layers[0];
    REQUIRE(std::get<std::vector<std::uint32_t>>(map_layer0.data).size() == 400);
    REQUIRE(map_layer0.height == 20);
    REQUIRE(map_layer0.name == "Background");
    REQUIRE(map_layer0.opacity == 1);
    REQUIRE(map_layer0.type == "tilelayer");
    REQUIRE(map_layer0.visible == true);
    REQUIRE(map_layer0.width == 20);
    REQUIRE(map_layer0.x == 0);
    REQUIRE(map_layer0.y == 0);
    const auto map_layer1 = map.layers[1];
    REQUIRE(map_layer1.draworder == "topdown");
    REQUIRE(map_layer1.name == "Objects");
    REQUIRE(map_layer1.objects.size() == 1);
    const auto map_layer1_object0 = map_layer1.objects[0];
    REQUIRE(map_layer1_object0.gid == 643);
    REQUIRE(map_layer1_object0.height == 16);
    REQUIRE(map_layer1_object0.id == 15);
    REQUIRE(map_layer1_object0.name == "");
    REQUIRE(map_layer1_object0.rotation == 0);
    REQUIRE(map_layer1_object0.type == "trunk");
    REQUIRE(map_layer1_object0.visible == true);
    REQUIRE(map_layer1_object0.width == 16);
    REQUIRE(map_layer1_object0.x == 176);
    REQUIRE(map_layer1_object0.y == 160);
    REQUIRE(map_layer1.opacity == 1);
    REQUIRE(map_layer1.type == "objectgroup");
    REQUIRE(map_layer1.visible == true);
    REQUIRE(map_layer1.x == 0);
    REQUIRE(map_layer1.y == 0);
    const auto map_layer2 = map.layers[2];
    REQUIRE(std::get<std::vector<std::uint32_t>>(map_layer2.data).size() == 400);
    REQUIRE(map_layer2.height == 20);
    REQUIRE(map_layer2.name == "Foreground");
    REQUIRE(map_layer2.opacity == 1);
    REQUIRE(map_layer2.type == "tilelayer");
    REQUIRE(map_layer2.visible == true);
    REQUIRE(map_layer2.width == 20);
    REQUIRE(map_layer2.x == 0);
    REQUIRE(map_layer2.y == 0);
    REQUIRE(map.nextobjectid == 16);
    REQUIRE(map.orientation == "orthogonal");
    REQUIRE(map.tiledversion == "1.1.6");
    REQUIRE(map.tileheight == 16);
    REQUIRE(map.tilesets.size() == 2);
    const auto map_tileset0 = map.tilesets[0];
    REQUIRE(map_tileset0.columns == 57);
    REQUIRE(map_tileset0.firstgid == 1);
    REQUIRE(map_tileset0.image == "../tilesets/rural.png");
    REQUIRE(map_tileset0.imageheight == 526);
    REQUIRE(map_tileset0.imagewidth == 968);
    REQUIRE(map_tileset0.margin == 0);
    REQUIRE(map_tileset0.name == "rural");
    REQUIRE(map_tileset0.spacing == 1);
    REQUIRE(map_tileset0.tilecount == 1767);
    REQUIRE(map_tileset0.tileheight == 16);
    REQUIRE(map_tileset0.tilewidth == 16);
    const auto map_tileset1 = map.tilesets[1];
    REQUIRE(map_tileset1.columns == 37);
    REQUIRE(map_tileset1.firstgid == 1768);
    REQUIRE(map_tileset1.image == "../tilesets/city.png");
    REQUIRE(map_tileset1.imageheight == 475);
    REQUIRE(map_tileset1.imagewidth == 628);
    REQUIRE(map_tileset1.margin == 0);
    REQUIRE(map_tileset1.name == "city");
    REQUIRE(map_tileset1.spacing == 1);
    REQUIRE(map_tileset1.tilecount == 1036);
    REQUIRE(map_tileset1.tileheight == 16);
    REQUIRE(map_tileset1.tilewidth == 16);
    REQUIRE(map.tilewidth == 16);
    REQUIRE(map.type == "map");
    REQUIRE(map.version == 1);
    REQUIRE(map.width == 20);
}
