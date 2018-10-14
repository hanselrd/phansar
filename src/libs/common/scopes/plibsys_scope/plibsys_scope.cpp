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

#include "plibsys_scope.hpp"
#include "../../utils/log/log.hpp"

namespace common {
namespace scopes {
plibsys_scope::plibsys_scope(const PMemVTable *vtable) {
    if (get_guards() > 1) {
        return;
    }

    if (vtable) {
        p_libsys_init_full(vtable);
        LOGI << "plibsys initialized (full)";
    } else {
        p_libsys_init();
        LOGI << "plibsys initialized";
    }
}

plibsys_scope::~plibsys_scope() {
    if (get_guards() > 1) {
        return;
    }

    p_libsys_shutdown();
    LOGI << "plibsys shutdown";
}
} // namespace scopes
} // namespace common