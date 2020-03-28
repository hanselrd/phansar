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

#ifndef APP_CLIENT_GRAPHICS_CANVAS_CANVAS_HPP
#define APP_CLIENT_GRAPHICS_CANVAS_CANVAS_HPP

#include <SDL2/SDL.h>
#include <common/components/color/color.hpp>
#include <common/components/vec2/vec2.hpp>
#include <cstdint>
#include <memory>

namespace client {
namespace graphics {
class canvas {
public:
    explicit canvas(common::components::vec2i size);

    void lock();
    void unlock();
    void set_draw_color(common::components::color color);
    void draw_point(common::components::vec2f point);
    void draw_line(common::components::vec2f point1, common::components::vec2f point2);
    std::shared_ptr<SDL_Texture> get_texture() const;

private:
    common::components::vec2i _size;
    std::shared_ptr<SDL_Texture> _texture;
    std::shared_ptr<SDL_PixelFormat> _format;
    std::uint32_t _color;
    std::uint32_t *_pixels;
    std::int32_t _pitch;
};
} // namespace graphics
} // namespace client

#endif
