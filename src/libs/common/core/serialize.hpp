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

#ifndef COMMON_CORE_SERIALIZE_HPP
#define COMMON_CORE_SERIALIZE_HPP

#include <cstdint>

namespace common {
namespace core {
namespace serialize {
std::uint16_t hton16(std::uint16_t host);
std::uint32_t hton32(std::uint32_t host);
std::uint64_t hton64(std::uint64_t host);
float htonf(float host);
double htond(double host);

std::uint16_t ntoh16(std::uint16_t net);
std::uint32_t ntoh32(std::uint32_t net);
std::uint64_t ntoh64(std::uint64_t net);
float ntohf(float net);
double ntohd(double net);
} // namespace serialize
} // namespace core
} // namespace common

#endif
