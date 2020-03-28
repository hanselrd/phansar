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
#include <common/utils/functions/functions.hpp>

namespace client {
namespace graphics {
polygon::polygon(common::components::vec2f position,
                 std::uint32_t radius,
                 std::uint32_t point_count,
                 common::components::color color,
                 bool filled)
    : shape{position, color, filled}, _radius{radius}, _canvas{
                                                           common::components::vec2i{_radius * 2,
                                                                                     _radius * 2}} {
    _canvas.set_draw_color(get_color());

    static const auto pi = float{std::atan(1.f) * 4};

    for (auto i = std::int32_t{0}; i < point_count; ++i) {
        auto angle = i * 2 * pi / point_count - pi / 2;
        _points.push_back(common::components::vec2f{_radius + (std::cos(angle) * _radius),
                                                    _radius + (std::sin(angle) * _radius)});
    }

    _canvas.lock();
    if (get_filled()) {
        for (auto i = std::int32_t{0}; i < _points.size() / 2; ++i) {
            auto points = common::utils::functions::interpolate(
                _points[i], (i < _points.size() - 1) ? _points[i + 1] : _points[0]);
            for (const auto &p : points) {
                _canvas.draw_line(common::components::vec2f{-p.x + _radius * 2, p.y},
                                  common::components::vec2f{p.x, p.y});
            }
        }
    } else {
        for (auto i = std::int32_t{0}; i < _points.size(); ++i) {
            auto point1 = _points[i];
            auto point2 = (i < _points.size() - 1) ? _points[i + 1] : _points[0];
            _canvas.draw_line(common::components::vec2f{point1.x, point1.y},
                              common::components::vec2f{point2.x, point2.y});
        }
    }
    _canvas.unlock();
}

// std::vector<common::components::vec2f> polygon::get_points() const {
//     return _points;
// }

void polygon::draw() {
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
