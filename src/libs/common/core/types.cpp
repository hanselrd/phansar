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

#include "types.hpp"

namespace common {
namespace core {
namespace types {
namespace lua_api {
void init(sol::table &t) {
    sol::table types = t.create_named("types");

    types.new_usertype<vector2f>("Vector2f",
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

    types.new_usertype<vector3f>("Vector3f",
                                 "new",
                                 sol::factories(
                                     [] {
                                         return vector3f{0, 0};
                                     },
                                     [](float x, float y, float z) {
                                         return vector3f{x, y, z};
                                     }),
                                 "x",
                                 &vector3f::x,
                                 "y",
                                 &vector3f::y,
                                 "z",
                                 &vector3f::z);
}
} // namespace lua_api
} // namespace types
} // namespace core
} // namespace common
