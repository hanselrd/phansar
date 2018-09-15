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

#ifndef COMMON_BITMASKS_PERMISSION_HPP
#define COMMON_BITMASKS_PERMISSION_HPP

#include <cstdint>
#include <type_traits>

namespace common {
namespace bitmasks {
enum permissions : std::uint8_t {
    NONE = 0,
    VETERAN = (1 << 0),
    DONOR = (1 << 1),
    INTERN = (1 << 2),
    ADVISOR = (1 << 3),
    MODERATOR = (1 << 4),
    ADMINISTRATOR = (1 << 5),
    OWNER = (1 << 6),
    ROOT = (1 << 7)
};

using permission_flags = std::underlying_type_t<permissions>;
} // namespace bitmasks
} // namespace common

#endif
