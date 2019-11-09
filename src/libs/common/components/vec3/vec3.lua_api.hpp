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

#ifndef LIBS_COMMON_COMPONENTS_VEC3_VEC3_LUA_API_HPP
#define LIBS_COMMON_COMPONENTS_VEC3_VEC3_LUA_API_HPP

#include "../../extlibs/sol/sol.hpp"

namespace lua_api {
namespace common {
namespace components {
void init_vec3(sol::table &t);
}
} // namespace common
} // namespace lua_api

#endif
