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

#include "layer.hpp"
#include "../../../../utils/log/log.hpp"
#include "../../../../utils/macros/macros.hpp"

namespace common {
namespace components {
namespace map_detail {
namespace format {
void to_json(extlibs::json &j, const _layer_ &l) {
    j = extlibs::json{{"chunks", l.chunks},
                      {"compression", l.compression},
                      {"data", l.data},
                      {"draworder", l.draworder},
                      {"encoding", l.encoding},
                      {"height", l.height},
                      {"id", l.id},
                      {"image", l.image},
                      {"layers", l.layers},
                      {"name", l.name},
                      {"objects", l.objects},
                      {"offsetx", l.offsetx},
                      {"offsety", l.offsety},
                      {"opacity", l.opacity},
                      {"properties", l.properties},
                      {"transparentcolor", l.transparentcolor},
                      {"type", l.type},
                      {"visible", l.visible},
                      {"width", l.width},
                      {"x", l.x},
                      {"y", l.y}};
}

void from_json(const extlibs::json &j, _layer_ &l) {
#define EXTRACT(field)                                                                             \
    [&] {                                                                                          \
        try {                                                                                      \
            j.at(STRINGIFY(field)).get_to(l.field);                                                \
        } catch (const extlibs::json::out_of_range &e) {                                           \
            LOGW << e.what();                                                                      \
        }                                                                                          \
    }()

    EXTRACT(chunks);
    EXTRACT(compression);
    EXTRACT(data);
    EXTRACT(draworder);
    EXTRACT(encoding);
    EXTRACT(height);
    EXTRACT(id);
    EXTRACT(image);
    EXTRACT(layers);
    EXTRACT(name);
    EXTRACT(objects);
    EXTRACT(offsetx);
    EXTRACT(offsety);
    EXTRACT(opacity);
    EXTRACT(properties);
    EXTRACT(transparentcolor);
    EXTRACT(type);
    EXTRACT(visible);
    EXTRACT(width);
    EXTRACT(x);
    EXTRACT(y);

#undef EXTRACT
}
} // namespace format
} // namespace map_detail
} // namespace components
} // namespace common
