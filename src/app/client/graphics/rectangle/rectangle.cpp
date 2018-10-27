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

#include "rectangle.hpp"
#include "../../managers/system_manager/system_manager.hpp"
#include <SDL2/SDL.h>

namespace client {
namespace graphics {
rectangle::rectangle(common::components::vec2f position,
                     common::components::vec2u size,
                     common::components::color color,
                     bool filled)
    : shape{position, color, filled}, _size{size} {
}

void rectangle::draw() {
    shape::draw();
    auto renderer = managers::system_manager::get_renderer();
    auto position = get_position();
    auto rect = SDL_Rect{static_cast<std::int32_t>(position.x),
                         static_cast<std::int32_t>(position.y),
                         static_cast<std::int32_t>(_size.x),
                         static_cast<std::int32_t>(_size.y)};
    if (get_filled()) {
        SDL_RenderFillRect(renderer.get(), &rect);
    } else {
        SDL_RenderDrawRect(renderer.get(), &rect);
    }
}
} // namespace graphics
} // namespace client
