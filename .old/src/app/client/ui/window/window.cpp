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

#include "window.hpp"

namespace client {
namespace ui {
window::window(const common::components::vec2f &position,
               const common::components::vec2u &size,
               const SDL_Color &color)
    : _titlebar{position, size, color}, _body{position, size, SDL_Color{0xAA, 0xAA, 0xAA, 0xDD}} {
    _titlebar.set_size(common::components::vec2u{size.x, 20});
    _body.set_position(common::components::vec2f{position.x, position.y + 20});
}

void window::update() {
}

void window::render() {
    _titlebar.render();
    _body.render();
}
} // namespace ui
} // namespace client
