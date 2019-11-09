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

#ifndef LIBS_COMMON_COMPONENTS_MAP_FORMAT_CHUNK_CHUNK_HPP
#define LIBS_COMMON_COMPONENTS_MAP_FORMAT_CHUNK_CHUNK_HPP

#include "../../../../extlibs/json/json.hpp"
#include <cstdint>
#include <string>
#include <variant>
#include <vector>

namespace common {
namespace components {
namespace map_detail {
namespace format {
struct _chunk_ {
    std::variant<std::vector<std::uint32_t>, std::string> data;
    std::uint32_t height;
    std::uint32_t width;
    std::uint32_t x;
    std::uint32_t y;
};

void to_json(extlibs::json &j, const _chunk_ &c);
void from_json(const extlibs::json &j, _chunk_ &c);
} // namespace format
} // namespace map_detail
} // namespace components
} // namespace common

#endif
