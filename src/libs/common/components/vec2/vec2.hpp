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

#ifndef COMMON_COMPONENTS_VEC2_HPP
#define COMMON_COMPONENTS_VEC2_HPP

#include <cstdint>
#include <type_traits>

namespace common {
namespace components {
template <class T> struct vec2 {
    static_assert(std::is_arithmetic_v<T>);

    T x{};
    T y{};
};

using vec2i = vec2<std::int32_t>;
using vec2u = vec2<std::uint32_t>;
using vec2f = vec2<float>;
using vec2d = vec2<double>;
} // namespace components
} // namespace common

#endif
