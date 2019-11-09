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

#ifndef LIBS_COMMON_COMPONENTS_MAP_FORMAT_TILE_TILE_HPP
#define LIBS_COMMON_COMPONENTS_MAP_FORMAT_TILE_TILE_HPP

#include "../../../../extlibs/json/json.hpp"
#include "../frame/frame.hpp"
#include "../layer/layer.hpp"
#include "../property/property.hpp"
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace common {
namespace components {
namespace map_detail {
namespace format {
struct _tile_ {
    std::vector<_frame_> animation;
    std::uint32_t id;
    std::optional<std::string> image;
    std::uint32_t imageheight;
    std::uint32_t imagewidth;
    std::optional<std::vector<_layer_>> objectgroup;
    std::vector<_property_> properties;
    std::vector<std::uint32_t> terrain;
    std::optional<std::string> type;
};

void to_json(extlibs::json &j, const _tile_ &t);
void from_json(const extlibs::json &j, _tile_ &t);
} // namespace format
} // namespace map_detail
} // namespace components
} // namespace common

#endif
