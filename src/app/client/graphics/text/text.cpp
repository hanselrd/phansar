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
#include <algorithm>
#include <common/utils/assert/assert.hpp>
#include <common/utils/log/log.hpp>
#include <type_traits>

namespace client {
namespace graphics {
text::text(common::components::vec2f position, TTF_Font *font, common::components::color color)
    : _position{position}, _font{font}, _color{color} {
}

void text::set_string(std::string_view str) {
    _str = str;
    _update();
}

void text::draw() {
    auto renderer = managers::system_manager::get_renderer();
    SDL_Rect src_rect{0, 0, _text_size.x, _text_size.y};
    SDL_Rect dst_rect{static_cast<std::int32_t>(_position.x),
                      static_cast<std::int32_t>(_position.y),
                      _text_size.x,
                      _text_size.y};
    SDL_RenderCopy(renderer.get(), _texture.get(), &src_rect, &dst_rect);
}

void text::_update() {
    if (_str.empty()) {
        return;
    }

    auto renderer = managers::system_manager::get_renderer();

    auto surface = TTF_RenderText_Blended(
        _font, _str.c_str(), SDL_Color{_color.r, _color.g, _color.b, _color.a});
    ASSERT(surface);

    TTF_SizeText(_font, _str.c_str(), &_text_size.x, &_text_size.y);

    if (!_texture || surface->w > _size.x || surface->h > _size.y) {
        _size.x = std::max(_size.x, surface->w);
        _size.y = std::max(_size.y, surface->h);
        LOGD("Resizing text to: {} * {}", _size.x, _size.y);
        _texture = std::shared_ptr<SDL_Texture>{SDL_CreateTexture(renderer.get(),
                                                                  surface->format->format,
                                                                  SDL_TEXTUREACCESS_STREAMING,
                                                                  _size.x,
                                                                  _size.y),
                                                &SDL_DestroyTexture};
        SDL_SetTextureAlphaMod(_texture.get(), _color.a);
        auto blend_mode = SDL_BlendMode{};
        SDL_GetRenderDrawBlendMode(renderer.get(), &blend_mode);
        SDL_SetTextureBlendMode(_texture.get(), blend_mode);
    }
    ASSERT(_texture);

    if (SDL_MUSTLOCK(surface)) {
        SDL_LockSurface(surface);
        SDL_UpdateTexture(_texture.get(), nullptr, surface->pixels, surface->pitch);
        SDL_UnlockSurface(surface);
    } else {
        SDL_UpdateTexture(_texture.get(), nullptr, surface->pixels, surface->pitch);
    }

    SDL_FreeSurface(surface);
}
} // namespace graphics
} // namespace client
