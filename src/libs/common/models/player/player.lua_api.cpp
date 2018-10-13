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

#include "player.lua_api.hpp"
#include "../entity/entity.hpp"
#include "player.hpp"

using namespace common;
using namespace common::models;

namespace lua_api {
namespace common {
namespace models {
void init_player(sol::table &t) {
    t.new_usertype<player>("Player",
                           sol::constructors<player()>(),
                           "name",
                           sol::property(&player::get_name, &player::set_name),
                           "permissions",
                           sol::readonly_property(&player::get_permissions),
                           sol::base_classes,
                           sol::bases<entity>());
}
} // namespace models
} // namespace common
} // namespace lua_api
