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

#include "vector2.lua_api.hpp"
#include "vector2.hpp"

using namespace common::components;

namespace lua_api {
namespace common {
namespace components {
void init_vector2(sol::table &t) {
    t.new_usertype<vector2f>("Vector2f",
                             "new",
                             sol::factories(
                                 [] {
                                     return vector2f{0, 0};
                                 },
                                 [](float x, float y) {
                                     return vector2f{x, y};
                                 }),
                             "x",
                             &vector2f::x,
                             "y",
                             &vector2f::y);
}
} // namespace components
} // namespace common
} // namespace lua_api
