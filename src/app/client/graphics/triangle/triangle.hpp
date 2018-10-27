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

#ifndef CLIENT_GRAPHICS_TRIANGLE_HPP
#define CLIENT_GRAPHICS_TRIANGLE_HPP

#include "../polygon/polygon.hpp"
#include <common/components/color/color.hpp>
#include <common/components/vec2/vec2.hpp>
#include <cstdint>

namespace client {
namespace graphics {
class triangle : public polygon {
public:
    explicit triangle(common::components::vec2f position,
                      std::uint32_t radius,
                      common::components::color color,
                      bool filled);
};
} // namespace graphics
} // namespace client

#endif
