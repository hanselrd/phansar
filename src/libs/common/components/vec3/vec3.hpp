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

#ifndef COMMON_COMPONENTS_VEC3_HPP
#define COMMON_COMPONENTS_VEC3_HPP

#include <cstdint>
#include <type_traits>

namespace common {
namespace components {
template <class T> struct vec3 {
    static_assert(std::is_arithmetic_v<T>);

    T x{};
    T y{};
    T z{};
};

using vec3i = vec3<std::int32_t>;
using vec3u = vec3<std::uint32_t>;
using vec3f = vec3<float>;
using vec3d = vec3<double>;
} // namespace components
} // namespace common

#endif
