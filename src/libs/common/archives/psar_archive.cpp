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

#include "psar_archive.hpp"
#include "../core/log.hpp"

namespace common {
namespace archives {
namespace psar_archive {
core::json load(std::istream &is) {
    auto j = core::json::from_cbor(is);
    LOGD << "Loaded " << core::json::to_cbor(j).size() << " bytes";
    return j;
}

void save(std::ostream &os, const core::json &j) {
    auto cbor = core::json::to_cbor(j);
    os.write(reinterpret_cast<const char *>(cbor.data()), cbor.size());
    LOGD << "Saved " << cbor.size() << " bytes";
}
} // namespace psar_archive
} // namespace archives
} // namespace common
