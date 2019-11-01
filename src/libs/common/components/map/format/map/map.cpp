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

#include "map.hpp"
#include "../../../../utils/log/log.hpp"
#include "../../../../utils/macros/macros.hpp"

namespace common {
namespace components {
namespace map_detail {
namespace format {
void to_json(extlibs::json &j, const _map_ &m) {
    j = extlibs::json{{"backgroundcolor", m.backgroundcolor},
                      {"height", m.height},
                      {"hexsidelength", m.hexsidelength},
                      {"infinite", m.infinite},
                      {"layers", m.layers},
                      {"nextlayerid", m.nextlayerid},
                      {"nextobjectid", m.nextobjectid},
                      {"orientation", m.orientation},
                      {"properties", m.properties},
                      {"renderorder", m.renderorder},
                      {"staggeraxis", m.staggeraxis},
                      {"staggerindex", m.staggerindex},
                      {"tiledversion", m.tiledversion},
                      {"tileheight", m.tileheight},
                      {"tilesets", m.tilesets},
                      {"tilewidth", m.tilewidth},
                      {"type", m.type},
                      {"version", m.version},
                      {"width", m.width}};
}

void from_json(const extlibs::json &j, _map_ &m) {
#define EXTRACT(field)                                                                             \
    [&] {                                                                                          \
        try {                                                                                      \
            j.at(STRINGIFY(field)).get_to(m.field);                                                \
        } catch (const extlibs::json::out_of_range &e) {                                           \
            LOGW(e.what());                                                                        \
        }                                                                                          \
    }()

    EXTRACT(backgroundcolor);
    EXTRACT(height);
    EXTRACT(hexsidelength);
    EXTRACT(infinite);
    EXTRACT(layers);
    EXTRACT(nextlayerid);
    EXTRACT(nextobjectid);
    EXTRACT(orientation);
    EXTRACT(properties);
    EXTRACT(renderorder);
    EXTRACT(staggeraxis);
    EXTRACT(staggerindex);
    EXTRACT(tiledversion);
    EXTRACT(tileheight);
    EXTRACT(tilesets);
    EXTRACT(tilewidth);
    EXTRACT(type);
    EXTRACT(version);
    EXTRACT(width);

#undef EXTRACT
}
} // namespace format
} // namespace map_detail
} // namespace components
} // namespace common
