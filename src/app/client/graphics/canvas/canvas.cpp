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
 *  but WITHOUT ANY WARRANTY{} without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with Phansar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "canvas.hpp"
#include "../../managers/system_manager/system_manager.hpp"
#include <common/utils/assert/assert.hpp>
#include <common/utils/functions/functions.hpp>

namespace client {
namespace graphics {
canvas::canvas(common::components::vec2i size) : _size{size}, _pixels{nullptr}, _pitch{0} {
    auto renderer = managers::system_manager::get_renderer();
    _texture = std::shared_ptr<SDL_Texture>{SDL_CreateTexture(renderer.get(),
                                                              SDL_PIXELFORMAT_RGBA8888,
                                                              SDL_TEXTUREACCESS_STREAMING,
                                                              _size.x,
                                                              _size.y),
                                            &SDL_DestroyTexture};
    ASSERT(_texture);
    auto blend_mode = SDL_BlendMode{};
    SDL_GetRenderDrawBlendMode(renderer.get(), &blend_mode);
    SDL_SetTextureBlendMode(_texture.get(), blend_mode);
    _format = std::shared_ptr<SDL_PixelFormat>{SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888),
                                               &SDL_FreeFormat};
    ASSERT(_format);
}

void canvas::lock() {
    ASSERT(!_pixels);
    ASSERT(!_pitch);
    SDL_LockTexture(_texture.get(), nullptr, reinterpret_cast<void **>(&_pixels), &_pitch);
    ASSERT(_pixels);
    ASSERT(_pitch);
}

void canvas::unlock() {
    ASSERT(_pixels);
    ASSERT(_pitch);
    SDL_UnlockTexture(_texture.get());
    _pixels = nullptr;
    _pitch = 0;
}

void canvas::set_draw_color(common::components::color color) {
    _color = SDL_MapRGBA(_format.get(), color.r, color.g, color.b, color.a);
}

void canvas::draw_point(common::components::vec2f point) {
    ASSERT(_pixels);
    ASSERT(_pitch);
    if (point.x > _size.x || point.y > _size.y) {
        return;
    }
    _pixels[static_cast<std::uint32_t>(point.x) +
            (_pitch / sizeof(std::uint32_t)) * static_cast<std::uint32_t>(point.y)] = _color;
}

void canvas::draw_line(common::components::vec2f point1, common::components::vec2f point2) {
    auto points = common::utils::functions::interpolate(point1, point2);
    for (const auto &p : points) {
        draw_point(p);
    }
}

std::shared_ptr<SDL_Texture> canvas::get_texture() const {
    ASSERT(!_pixels);
    ASSERT(!_pitch);
    ASSERT(_texture);
    return _texture;
}
} // namespace graphics
} // namespace client
