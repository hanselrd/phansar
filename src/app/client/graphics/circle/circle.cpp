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
#include <common/utils/assert/assert.hpp>

namespace client {
namespace graphics {
circle::circle(common::components::vec2f position,
               std::uint32_t radius,
               common::components::color color,
               bool filled)
    : shape{position, color, filled}, _radius{radius}, _canvas{
                                                           common::components::vec2i{_radius * 2,
                                                                                     _radius * 2}} {
    _canvas.set_draw_color(get_color());

    auto x = static_cast<std::int32_t>(_radius - 1);
    auto y = std::int32_t{0};
    auto dx = std::int32_t{1};
    auto dy = std::int32_t{1};
    auto err = static_cast<std::int32_t>(dx - (_radius << 1));

    _canvas.lock();
    while (x >= y) {
        if (get_filled()) {
            _canvas.draw_line(common::components::vec2f{_radius - y, _radius - x},
                              common::components::vec2f{_radius + y, _radius - x});
            _canvas.draw_line(common::components::vec2f{_radius - x, _radius - y},
                              common::components::vec2f{_radius + x, _radius - y});
            _canvas.draw_line(common::components::vec2f{_radius - x, _radius + y},
                              common::components::vec2f{_radius + x, _radius + y});
            _canvas.draw_line(common::components::vec2f{_radius - y, _radius + x},
                              common::components::vec2f{_radius + y, _radius + x});
        } else {
            _canvas.draw_point(common::components::vec2f{_radius + x, _radius + y});
            _canvas.draw_point(common::components::vec2f{_radius + y, _radius + x});
            _canvas.draw_point(common::components::vec2f{_radius - y, _radius + x});
            _canvas.draw_point(common::components::vec2f{_radius - x, _radius + y});
            _canvas.draw_point(common::components::vec2f{_radius - x, _radius - y});
            _canvas.draw_point(common::components::vec2f{_radius - y, _radius - x});
            _canvas.draw_point(common::components::vec2f{_radius + y, _radius - x});
            _canvas.draw_point(common::components::vec2f{_radius + x, _radius - y});
        }

        if (err <= 0) {
            ++y;
            err += dy;
            dy += 2;
        }

        if (err > 0) {
            --x;
            dx += 2;
            err += dx - (_radius << 1);
        }
    }
    _canvas.unlock();
}

void circle::draw() {
    auto renderer = managers::system_manager::get_renderer();
    auto position = get_position();
    SDL_Rect rect{static_cast<std::int32_t>(position.x),
                  static_cast<std::int32_t>(position.y),
                  _radius * 2,
                  _radius * 2};
    SDL_RenderCopy(renderer.get(), _canvas.get_texture().get(), nullptr, &rect);
}
} // namespace graphics
} // namespace client
