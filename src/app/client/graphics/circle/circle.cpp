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

#include "circle.hpp"
#include "../../managers/system_manager/system_manager.hpp"
#include <SDL2/SDL.h>

namespace client {
namespace graphics {
circle::circle(common::components::vec2f position,
               std::uint32_t radius,
               common::components::color color,
               bool filled)
    : shape{position, color, filled}, _radius{radius} {
}

void circle::draw() {
    shape::draw();
    auto renderer = managers::system_manager::get_renderer();
    auto position = get_position();

    auto x = static_cast<std::int32_t>(_radius - 1);
    auto y = std::int32_t{0};
    auto dx = std::int32_t{1};
    auto dy = std::int32_t{1};
    auto err = static_cast<std::int32_t>(dx - (_radius << 1));
    auto x_dec = bool{false};

    while (x >= y) {
        if (!get_filled()) {
            SDL_RenderDrawPoint(renderer.get(), position.x + x, position.y + y);
            SDL_RenderDrawPoint(renderer.get(), position.x + y, position.y + x);
            SDL_RenderDrawPoint(renderer.get(), position.x - y, position.y + x);
            SDL_RenderDrawPoint(renderer.get(), position.x - x, position.y + y);
            SDL_RenderDrawPoint(renderer.get(), position.x - x, position.y - y);
            SDL_RenderDrawPoint(renderer.get(), position.x - y, position.y - x);
            SDL_RenderDrawPoint(renderer.get(), position.x + y, position.y - x);
            SDL_RenderDrawPoint(renderer.get(), position.x + x, position.y - y);
        } else {
            if (x_dec && x != y)
                SDL_RenderDrawLine(
                    renderer.get(), position.x - y, position.y - x, position.x + y, position.y - x);
            if (y != 0)
                SDL_RenderDrawLine(
                    renderer.get(), position.x - x, position.y - y, position.x + x, position.y - y);
            if (x != y)
                SDL_RenderDrawLine(
                    renderer.get(), position.x - x, position.y + y, position.x + x, position.y + y);
            if (x_dec)
                SDL_RenderDrawLine(
                    renderer.get(), position.x - y, position.y + x, position.x + y, position.y + x);
        }

        if (err <= 0) {
            ++y;
            err += dy;
            dy += 2;
            x_dec = false;
        }

        if (err > 0) {
            --x;
            dx += 2;
            err += dx - (_radius << 1);
            x_dec = true;
        }
    }
}
} // namespace graphics
} // namespace client
