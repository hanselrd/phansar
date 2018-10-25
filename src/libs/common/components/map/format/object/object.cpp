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

#include "object.hpp"
#include "../../../../utils/log/log.hpp"
#include "../../../../utils/macros/macros.hpp"

namespace common {
namespace components {
namespace map_detail {
namespace format {
void to_json(extlibs::json &j, const _object_ &o) {
    j = extlibs::json{{"ellipse", o.ellipse},
                      {"gid", o.ellipse},
                      {"id", o.id},
                      {"height", o.height},
                      {"name", o.name},
                      {"point", o.point},
                      {"polygon", o.polygon},
                      {"polyline", o.polyline},
                      {"properties", o.properties},
                      {"rotation", o.rotation},
                      {"template", o.template_file},
                      {"text", o.text},
                      {"type", o.type},
                      {"visible", o.visible},
                      {"width", o.width},
                      {"x", o.x},
                      {"y", o.y}};
}

void from_json(const extlibs::json &j, _object_ &o) {
#define EXTRACT_HELPER(key, field)                                                                 \
    [&] {                                                                                          \
        try {                                                                                      \
            j.at(key).get_to(o.field);                                                             \
        } catch (const extlibs::json::out_of_range &e) {                                           \
            LOGW << e.what();                                                                      \
        }                                                                                          \
    }()
#define EXTRACT(field) EXTRACT_HELPER(STRINGIFY(field), field)

    EXTRACT(ellipse);
    EXTRACT(gid);
    EXTRACT(id);
    EXTRACT(height);
    EXTRACT(name);
    EXTRACT(point);
    EXTRACT(polygon);
    EXTRACT(polyline);
    EXTRACT(properties);
    EXTRACT(rotation);
    EXTRACT_HELPER("template", template_file);
    EXTRACT(text);
    EXTRACT(type);
    EXTRACT(visible);
    EXTRACT(width);
    EXTRACT(x);
    EXTRACT(y);

#undef EXTRACT_HELPER
#undef EXTRACT
}
} // namespace format
} // namespace map_detail
} // namespace components
} // namespace common
