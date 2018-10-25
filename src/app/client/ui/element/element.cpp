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

#include "element.hpp"
#include "../../managers/system_manager/system_manager.hpp"

namespace client {
namespace ui {
element::element()
    : element(common::components::vec2f{0.f, 0.f},
              common::components::vec2u{0, 0},
              SDL_Color{0xFF, 0xFF, 0xFF, 0xFF}) {
}

element::element(const common::components::vec2f &position,
                 const common::components::vec2u &size,
                 const SDL_Color &color)
    : _position{position}, _size{size}, _color{color} {
}

const common::components::vec2f &element::get_position() const {
    return _position;
}

void element::set_position(const common::components::vec2f &position) {
    _position = position;
}

const common::components::vec2u &element::get_size() const {
    return _size;
}

void element::set_size(const common::components::vec2u &size) {
    _size = size;
}

const SDL_Color &element::get_color() const {
    return _color;
}

void element::set_color(const SDL_Color &color) {
    _color = color;
}

void element::add_element(const std::shared_ptr<element> &el) {
    _elements.push_back(el);
}

void element::_set_render_draw_color() {
    SDL_SetRenderDrawColor(
        managers::system_manager::get_renderer().get(), _color.r, _color.g, _color.b, _color.a);
}

SDL_Rect *element::_get_rect() {
    _rect.x = _position.x;
    _rect.y = _position.y;
    _rect.w = _size.x;
    _rect.h = _size.y;
    return &_rect;
}
} // namespace ui
} // namespace client
