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

#include "permissions.lua_api.hpp"
#include "permissions.hpp"

using namespace common::bitmasks;

namespace lua_api {
namespace common {
namespace bitmasks {
void init_permissions(sol::table &t) {
    t.new_enum("Permissions",
               "NONE",
               permissions::NONE,
               "VETERAN",
               permissions::VETERAN,
               "DONOR",
               permissions::DONOR,
               "INTERN",
               permissions::INTERN,
               "ADVISOR",
               permissions::ADVISOR,
               "MODERATOR",
               permissions::MODERATOR,
               "ADMINISTRATOR",
               permissions::ADMINISTRATOR,
               "OWNER",
               permissions::OWNER,
               "ROOT",
               permissions::ROOT);
}
} // namespace bitmasks
} // namespace common
} // namespace lua_api
