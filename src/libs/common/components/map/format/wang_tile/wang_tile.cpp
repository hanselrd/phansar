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

#include "wang_tile.hpp"
#include "../../../../utils/log/log.hpp"
#include "../../../../utils/macros/macros.hpp"

namespace common {
namespace components {
namespace map_detail {
namespace format {
void to_json(vendor::json &j, const _wang_tile_ &wt) {
    j = vendor::json{{"dflip", wt.dflip},
                     {"hflip", wt.hflip},
                     {"tileid", wt.tileid},
                     {"vflip", wt.vflip},
                     {"wangid", wt.wangid}};
}

void from_json(const vendor::json &j, _wang_tile_ &wt) {
#define EXTRACT(field)                                                                             \
    [&] {                                                                                          \
        try {                                                                                      \
            j.at(STRINGIFY(field)).get_to(wt.field);                                               \
        } catch (const vendor::json::out_of_range &e) {                                            \
            LOGW(e.what());                                                                        \
        }                                                                                          \
    }()

    EXTRACT(dflip);
    EXTRACT(hflip);
    EXTRACT(tileid);
    EXTRACT(vflip);
    EXTRACT(wangid);

#undef EXTRACT
}
} // namespace format
} // namespace map_detail
} // namespace components
} // namespace common
