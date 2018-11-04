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

#ifndef COMMON_UTILS_FUNCTIONS_HPP
#define COMMON_UTILS_FUNCTIONS_HPP

#include "../../components/vec2/vec2.hpp"
#include "../../components/vec3/vec3.hpp"
#include <vector>

namespace common {
namespace utils {
namespace functions {
template <class T>
std::vector<components::vec2<T>> interpolate(components::vec2<T> point1,
                                             components::vec2<T> point2);

template <class T>
std::vector<components::vec3<T>> interpolate(components::vec3<T> point1,
                                             components::vec3<T> point2);
} // namespace functions
} // namespace utils
} // namespace common

#include "functions.tpp"

#endif
