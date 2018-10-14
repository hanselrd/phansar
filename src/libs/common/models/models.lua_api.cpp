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

#include "models.lua_api.hpp"
#include "entity/entity.lua_api.hpp"
#include "player/player.lua_api.hpp"

namespace lua_api {
namespace common {
void init_models(sol::table &t) {
    auto models = t.create_named("models");

    models::init_entity(models);
    models::init_player(models);
}
} // namespace common
} // namespace lua_api