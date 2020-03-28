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
#include "../../utils/log/log.hpp"

namespace common {
namespace archives {
vendor::json psar_archive::load(std::istream &is) {
    auto j = vendor::json::from_cbor(is);
    LOGD("Loaded {} bytes", vendor::json::to_cbor(j).size());
    return j;
}

void psar_archive::save(std::ostream &os, const vendor::json &j) {
    auto cbor = vendor::json::to_cbor(j);
    os.write(reinterpret_cast<const char *>(cbor.data()), cbor.size());
    LOGD("Saved {} bytes", cbor.size());
}
} // namespace archives
} // namespace common
