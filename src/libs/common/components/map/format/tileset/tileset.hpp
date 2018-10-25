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

#ifndef COMMON_COMPONENTS_MAP_FORMAT_TILESET_HPP
#define COMMON_COMPONENTS_MAP_FORMAT_TILESET_HPP

#include "../../../../extlibs/json/json.hpp"
#include "../grid/grid.hpp"
#include "../point2/point2.hpp"
#include "../property/property.hpp"
#include "../terrain/terrain.hpp"
#include "../tile/tile.hpp"
#include "../wang_set/wang_set.hpp"
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace common {
namespace components {
namespace map_detail {
namespace format {
struct _tileset_ {
    std::uint32_t columns;
    std::uint32_t firstgid;
    std::optional<_grid_> grid;
    std::string image;
    std::uint32_t imagewidth;
    std::uint32_t imageheight;
    std::uint32_t margin;
    std::string name;
    std::vector<_property_> properties;
    std::uint32_t spacing;
    std::optional<std::vector<_terrain_>> terrains;
    std::uint32_t tilecount;
    std::uint32_t tileheight;
    std::optional<_point2_> tileoffset;
    std::optional<std::vector<_tile_>> tiles;
    std::uint32_t tilewidth;
    std::optional<std::string> transparentcolor;
    std::string type;
    std::vector<_wang_set_> wangsets;
};

void to_json(extlibs::json &j, const _tileset_ &t);
void from_json(const extlibs::json &j, _tileset_ &t);
} // namespace format
} // namespace map_detail
} // namespace components
} // namespace common

#endif
