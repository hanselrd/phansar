/**
 *  This file is part of Phansar.
 *
 *  Copyright (C) 2018  Hansel De La Cruz
 *
 *  Phansar is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Phansar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with Phansar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "functions.hpp"
#include <algorithm>
#include <cmath>

namespace common {
namespace utils {
namespace functions {
template <class T>
std::vector<components::vec2<T>> interpolate(components::vec2<T> point1,
                                             components::vec2<T> point2) {
    auto points = std::vector<components::vec2<T>>{};
    auto dx = point2.x - point1.x;
    auto dy = point2.y - point1.y;
    auto steps = std::max(std::abs(dx), std::abs(dy));
    auto x_inc = dx / steps;
    auto y_inc = dy / steps;
    auto [x, y] = point1;

    for (auto i = std::int32_t{0}; i <= steps; ++i) {
        points.push_back(common::components::vec2<T>{x, y});
        x += x_inc;
        y += y_inc;
    }

    return points;
}

template <class T>
std::vector<components::vec3<T>> interpolate(components::vec3<T> point1,
                                             components::vec3<T> point2) {
    auto points = std::vector<components::vec3<T>>{};
    auto dx = point2.x - point1.x;
    auto dy = point2.y - point1.y;
    auto dz = point2.z - point1.z;
    auto steps = std::max(std::max(std::abs(dx), std::abs(dy)), std::abs(dz));
    auto x_inc = dx / steps;
    auto y_inc = dy / steps;
    auto z_inc = dz / steps;
    auto [x, y, z] = point1;

    for (auto i = std::int32_t{0}; i <= steps; ++i) {
        points.push_back(common::components::vec3<T>{x, y, z});
        x += x_inc;
        y += y_inc;
        z += z_inc;
    }

    return points;
}
} // namespace functions
} // namespace utils
} // namespace common
