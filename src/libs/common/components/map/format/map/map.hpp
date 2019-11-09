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

#ifndef LIBS_COMMON_COMPONENTS_MAP_FORMAT_MAP_MAP_HPP
#define LIBS_COMMON_COMPONENTS_MAP_FORMAT_MAP_MAP_HPP

#include "../../../../extlibs/json/json.hpp"
#include "../layer/layer.hpp"
#include "../property/property.hpp"
#include "../tileset/tileset.hpp"
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace common {
namespace components {
namespace map_detail {
namespace format {
struct _map_ {
    std::optional<std::string> backgroundcolor;
    std::uint32_t height;
    std::uint32_t hexsidelength;
    bool infinite;
    std::vector<_layer_> layers;
    std::uint32_t nextlayerid;
    std::uint32_t nextobjectid;
    std::string orientation;
    std::vector<_property_> properties;
    std::string renderorder;
    std::string staggeraxis;
    std::string staggerindex;
    std::string tiledversion;
    std::uint32_t tileheight;
    std::vector<_tileset_> tilesets;
    std::uint32_t tilewidth;
    std::string type;
    double version;
    std::uint32_t width;
};

void to_json(extlibs::json &j, const _map_ &m);
void from_json(const extlibs::json &j, _map_ &m);
} // namespace format
} // namespace map_detail
} // namespace components
} // namespace common

#endif
