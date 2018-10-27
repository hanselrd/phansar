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

#ifndef CLIENT_GRAPHICS_POLYGON_HPP
#define CLIENT_GRAPHICS_POLYGON_HPP

#include "../shape/shape.hpp"
#include <common/components/color/color.hpp>
#include <common/components/vec2/vec2.hpp>
#include <cstdint>
#include <vector>

namespace client {
namespace graphics {
class polygon : public shape {
public:
    explicit polygon(common::components::vec2f position,
                     std::uint32_t radius,
                     std::uint32_t point_count,
                     common::components::color color,
                     bool filled /*buggy*/);
    virtual ~polygon() = default;

    std::vector<common::components::vec2f> get_points() const;
    virtual void draw() override;

private:
    std::uint32_t _radius;
    std::vector<common::components::vec2f> _points;
};
} // namespace graphics
} // namespace client

#endif
