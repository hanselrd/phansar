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

#include "shape.hpp"
#include "../../managers/system_manager/system_manager.hpp"
#include <SDL2/SDL.h>

namespace client {
namespace graphics {
shape::shape(common::components::vec2f position, common::components::color color, bool filled)
    : _position{position}, _color{color}, _filled{filled} {
}

common::components::vec2f shape::get_position() const {
    return _position;
}

void shape::set_position(common::components::vec2f position) {
    _position = position;
}

void shape::move(common::components::vec2f offset) {
    _position.x += offset.x;
    _position.y += offset.y;
}

common::components::color shape::get_color() const {
    return _color;
}

void shape::set_color(common::components::color color) {
    _color = color;
}

void shape::color_shift(common::components::color offset) {
    _color.r += offset.r;
    _color.g += offset.g;
    _color.b += offset.b;
    _color.a += offset.a;
}

bool shape::get_filled() const {
    return _filled;
}

void shape::set_filled(bool filled) {
    _filled = filled;
}

void shape::draw() {
    auto renderer = managers::system_manager::get_renderer();
    SDL_SetRenderDrawColor(renderer.get(), _color.r, _color.g, _color.b, _color.a);
}
} // namespace graphics
} // namespace client
