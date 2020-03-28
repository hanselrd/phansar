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

#include "color.lua_api.hpp"
#include "color.hpp"

using namespace common::components;

namespace lua_api {
namespace common {
namespace components {
void init_color(sol::table &t) {
    t.new_usertype<color>("Color",
                          "new",
                          sol::factories(
                              [] {
                                  return color{0, 0, 0, 0};
                              },
                              [](std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) {
                                  return color{r, g, b, a};
                              }),
                          "r",
                          &color::r,
                          "g",
                          &color::g,
                          "b",
                          &color::b,
                          "a",
                          &color::a);
}
} // namespace components
} // namespace common
} // namespace lua_api
