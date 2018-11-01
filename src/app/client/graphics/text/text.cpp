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
 * but WITHOUT ANY WARRANTY{} without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with Phansar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "text.hpp"
#include "../../managers/system_manager/system_manager.hpp"
#include <SDL2/SDL.h>
#include <common/utils/assert/assert.hpp>
#include <type_traits>

namespace client {
namespace graphics {
text::text(common::components::vec2f position,
           TTF_Font *font,
           type type,
           common::components::color color)
    : _position{position}, _font{font}, _type{type}, _color{color} {
}

void text::set_string(std::string_view str) {
    auto surface = std::add_pointer_t<SDL_Surface>{nullptr};

    switch (_type) {
    case type::BLENDED:
        surface = TTF_RenderText_Blended(
            _font, str.data(), SDL_Color{_color.r, _color.g, _color.b, _color.a});
        break;
    case type::BLENDED_WRAPPED:
        ASSERT(0);
        break;
    case type::SHADED:
        surface = TTF_RenderText_Shaded(_font,
                                        str.data(),
                                        SDL_Color{_color.r, _color.g, _color.b, _color.a},
                                        SDL_Color{0x00, 0x00, 0x00, 0xFF});
        break;
    case type::SOLID:
        surface = TTF_RenderText_Solid(
            _font, str.data(), SDL_Color{_color.r, _color.g, _color.b, _color.a});
        break;
    }

    ASSERT(surface);
    auto renderer = managers::system_manager::get_renderer();
    _texture = std::shared_ptr<SDL_Texture>{SDL_CreateTextureFromSurface(renderer.get(), surface),
                                            &SDL_DestroyTexture};
    ASSERT(_texture);
    SDL_FreeSurface(surface);

    TTF_SizeText(_font, str.data(), &_size.x, &_size.y);
}

void text::draw() {
    auto renderer = managers::system_manager::get_renderer();
    SDL_Rect rect{static_cast<std::int32_t>(_position.x),
                  static_cast<std::int32_t>(_position.y),
                  _size.x,
                  _size.y};
    SDL_RenderCopy(renderer.get(), _texture.get(), nullptr, &rect);
}
} // namespace graphics
} // namespace client
