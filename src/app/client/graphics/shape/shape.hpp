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

#ifndef CLIENT_GRAPHICS_SHAPE_HPP
#define CLIENT_GRAPHICS_SHAPE_HPP

#include <common/components/color/color.hpp>
#include <common/components/vec2/vec2.hpp>

namespace client {
namespace graphics {
class shape {
protected:
    explicit shape(common::components::vec2f position,
                   common::components::color color,
                   bool filled);

public:
    virtual ~shape() = default;

    common::components::vec2f get_position() const;
    void set_position(common::components::vec2f position);
    void move(common::components::vec2f offset);
    common::components::color get_color() const;
    void set_color(common::components::color color);
    void color_shift(common::components::color offset);
    bool get_filled() const;
    void set_filled(bool filled);
    virtual void draw();

private:
    common::components::vec2f _position;
    common::components::color _color;
    bool _filled;
};
} // namespace graphics
} // namespace client

#endif
