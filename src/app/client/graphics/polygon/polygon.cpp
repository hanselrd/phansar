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

#include "polygon.hpp"
#include "../../managers/system_manager/system_manager.hpp"
#include <SDL2/SDL.h>
#include <cmath>

namespace client {
namespace graphics {
polygon::polygon(common::components::vec2f position,
                 std::uint32_t radius,
                 std::uint32_t point_count,
                 common::components::color color,
                 bool filled)
    : shape{position, color, filled}, _radius{radius} {
    static const auto pi = float{std::atan(1.f) * 4};

    for (auto i = std::int32_t{0}; i < point_count; ++i) {
        auto angle = i * 2 * pi / point_count - pi / 2;
        _points.push_back(common::components::vec2f{_radius + (std::cos(angle) * _radius),
                                                    _radius + (std::sin(angle) * _radius)});
    }
}

std::vector<common::components::vec2f> polygon::get_points() const {
    return _points;
}

void polygon::draw() {
    shape::draw();
    auto renderer = managers::system_manager::get_renderer();
    auto position = get_position();
    if (get_filled()) {
        for (auto i = std::uint32_t{0}; i < _points.size() / 2; ++i) {
            auto point0 = _points[i];
            auto point1 = (i < _points.size() - 1) ? _points[i + 1] : _points[0];
            auto dx = point1.x - point0.x;
            auto dy = point1.y - point0.y;
            auto steps = std::abs(dx) > std::abs(dy) ? std::abs(dx) : std::abs(dy);
            auto x_inc = dx / steps;
            auto y_inc = dy / steps;
            auto [x, y] = point0;

            for (auto i = std::int32_t{0}; i <= steps; ++i) {
                if (std::floor(y + y_inc) > y) {
                    SDL_RenderDrawLine(renderer.get(),
                                       position.x - x + _radius * 2,
                                       position.y + y,
                                       position.x + x,
                                       position.y + y);
                }
                x += x_inc;
                y += y_inc;
            }
        }
    } else {
        for (auto i = std::uint32_t{0}; i < _points.size(); ++i) {
            auto point0 = _points[i];
            auto point1 = (i < _points.size() - 1) ? _points[i + 1] : _points[0];
            SDL_RenderDrawLine(renderer.get(),
                               position.x + point0.x,
                               position.y + point0.y,
                               position.x + point1.x,
                               position.y + point1.y);
        }
    }
}
} // namespace graphics
} // namespace client
