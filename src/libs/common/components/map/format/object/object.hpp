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

#ifndef LIBS_COMMON_COMPONENTS_MAP_FORMAT_OBJECT_OBJECT_HPP
#define LIBS_COMMON_COMPONENTS_MAP_FORMAT_OBJECT_OBJECT_HPP

#include "../../../../vendor/json/json.hpp"
#include "../point2/point2.hpp"
#include "../property/property.hpp"
#include "../text/text.hpp"
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace common {
namespace components {
namespace map_detail {
namespace format {
struct _object_ {
    bool ellipse;
    std::uint32_t gid;
    double height;
    std::uint32_t id;
    std::string name;
    bool point;
    std::vector<_point2_> polygon;
    std::vector<_point2_> polyline;
    std::vector<_property_> properties;
    double rotation;
    std::string template_file;
    std::optional<_text_> text;
    std::string type;
    bool visible;
    double width;
    double x;
    double y;
};

void to_json(vendor::json &j, const _object_ &o);
void from_json(const vendor::json &j, _object_ &o);
} // namespace format
} // namespace map_detail
} // namespace components
} // namespace common

#endif
