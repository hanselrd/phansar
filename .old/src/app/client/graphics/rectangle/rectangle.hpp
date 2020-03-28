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

#ifndef APP_CLIENT_GRAPHICS_RECTANGLE_RECTANGLE_HPP
#define APP_CLIENT_GRAPHICS_RECTANGLE_RECTANGLE_HPP

#include "../shape/shape.hpp"
#include <common/components/color/color.hpp>
#include <common/components/vec2/vec2.hpp>

namespace client {
namespace graphics {
class rectangle : public shape {
public:
    explicit rectangle(common::components::vec2f position,
                       common::components::vec2u size,
                       common::components::color color,
                       bool filled);

    virtual void draw() override;

private:
    common::components::vec2u _size;
};
} // namespace graphics
} // namespace client

#endif
