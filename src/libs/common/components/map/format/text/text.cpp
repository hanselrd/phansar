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

#include "text.hpp"
#include "../../../../utils/log/log.hpp"
#include "../../../../utils/macros/macros.hpp"

namespace common {
namespace components {
namespace map_detail {
namespace format {
void to_json(extlibs::json &j, const _text_ &t) {
    j = extlibs::json{{"text", t.text}, {"wrap", t.wrap}};
}

void from_json(const extlibs::json &j, _text_ &t) {
#define EXTRACT(field)                                                                             \
    [&] {                                                                                          \
        try {                                                                                      \
            j.at(STRINGIFY(field)).get_to(t.field);                                                \
        } catch (const extlibs::json::out_of_range &e) {                                           \
            LOGW << e.what();                                                                      \
        }                                                                                          \
    }()

    EXTRACT(text);
    EXTRACT(wrap);

#undef EXTRACT
}
} // namespace format
} // namespace map_detail
} // namespace components
} // namespace common
