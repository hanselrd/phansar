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

#ifndef APP_CLIENT_GRAPHICS_TEXT_TEXT_HPP
#define APP_CLIENT_GRAPHICS_TEXT_TEXT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <common/components/color/color.hpp>
#include <common/components/vec2/vec2.hpp>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>

namespace client {
namespace graphics {
class text {
public:
    explicit text(common::components::vec2f position,
                  TTF_Font *font,
                  common::components::color color);

    void set_string(std::string_view str);
    void draw();

private:
    void _update();

    common::components::vec2f _position;
    common::components::vec2i _size;
    common::components::vec2i _text_size;
    TTF_Font *_font;
    common::components::color _color;
    std::shared_ptr<SDL_Texture> _texture;
    std::string _str;
};
} // namespace graphics
} // namespace client

#endif
