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

#include "enet_scope.hpp"
#include "../../utils/assert/assert.hpp"
#include "../../utils/log/log.hpp"

namespace common {
namespace scopes {
enet_scope::enet_scope() {
    if (get_guards() > 1) {
        return;
    }

    ASSERT_ALWAYS(enet_initialize() == 0);
    LOGI << "ENet initialized";
}

enet_scope::~enet_scope() {
    if (get_guards() > 1) {
        return;
    }

    enet_deinitialize();
    LOGI << "ENet shutdown";
}
} // namespace scopes
} // namespace common
