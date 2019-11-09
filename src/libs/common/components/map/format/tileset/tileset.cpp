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

#include "tileset.hpp"
#include "../../../../utils/log/log.hpp"
#include "../../../../utils/macros/macros.hpp"

namespace common {
namespace components {
namespace map_detail {
namespace format {
void to_json(vendor::json &j, const _tileset_ &t) {
    j = vendor::json{{"columns", t.columns},
                     {"firstgid", t.firstgid},
                     {"grid", t.grid},
                     {"image", t.image},
                     {"imagewidth", t.imagewidth},
                     {"imageheight", t.imageheight},
                     {"margin", t.margin},
                     {"name", t.name},
                     {"properties", t.properties},
                     {"spacing", t.spacing},
                     {"terrains", t.terrains},
                     {"tilecount", t.tilecount},
                     {"tileheight", t.tileheight},
                     {"tileoffset", t.tileoffset},
                     {"tiles", t.tiles},
                     {"tilewidth", t.tilewidth},
                     {"transparentcolor", t.transparentcolor},
                     {"type", t.type},
                     {"wangsets", t.wangsets}};
}

void from_json(const vendor::json &j, _tileset_ &t) {
#define EXTRACT(field)                                                                             \
    [&] {                                                                                          \
        try {                                                                                      \
            j.at(STRINGIFY(field)).get_to(t.field);                                                \
        } catch (const vendor::json::out_of_range &e) {                                            \
            LOGW(e.what());                                                                        \
        }                                                                                          \
    }()

    EXTRACT(columns);
    EXTRACT(firstgid);
    EXTRACT(grid);
    EXTRACT(image);
    EXTRACT(imagewidth);
    EXTRACT(imageheight);
    EXTRACT(margin);
    EXTRACT(name);
    EXTRACT(properties);
    EXTRACT(spacing);
    EXTRACT(terrains);
    EXTRACT(tilecount);
    EXTRACT(tileheight);
    EXTRACT(tileoffset);
    EXTRACT(tiles);
    EXTRACT(tilewidth);
    EXTRACT(transparentcolor);
    EXTRACT(type);
    EXTRACT(wangsets);

#undef EXTRACT
}
} // namespace format
} // namespace map_detail
} // namespace components
} // namespace common
