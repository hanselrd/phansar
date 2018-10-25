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

#ifndef COMMON_COMPONENTS_MAP_FORMAT_WANG_TILE_HPP
#define COMMON_COMPONENTS_MAP_FORMAT_WANG_TILE_HPP

#include "../../../../extlibs/json/json.hpp"
#include <array>
#include <cstdint>

namespace common {
namespace components {
namespace map_detail {
namespace format {
struct _wang_tile_ {
    bool dflip;
    bool hflip;
    std::uint32_t tileid;
    bool vflip;
    std::array<std::uint8_t, 8> wangid;
};

void to_json(extlibs::json &j, const _wang_tile_ &wt);
void from_json(const extlibs::json &j, _wang_tile_ &wt);
} // namespace format
} // namespace map_detail
} // namespace components
} // namespace common

#endif
