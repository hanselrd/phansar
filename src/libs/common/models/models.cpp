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

#include "models.hpp"

namespace common {
namespace models {
namespace lua_api {
void init(sol::table &t) {
    sol::table models = t.create_named("models");

    models.new_usertype<entity>(
        "Entity",
        sol::constructors<entity(), entity(const core::types::vector3f &)>(),
        "move",
        &entity::move,
        "map_id",
        sol::property(&entity::get_map_id, &entity::set_map_id),
        "position",
        sol::property(&entity::get_position, &entity::set_position));

    models.new_usertype<player>("Player",
                                sol::constructors<player()>(),
                                "name",
                                sol::property(&player::get_name, &player::set_name),
                                "permissions",
                                sol::readonly_property(&player::get_permissions),
                                sol::base_classes,
                                sol::bases<entity>());
}
} // namespace lua_api
} // namespace models
} // namespace common
