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

#ifndef APP_CLIENT_MANAGEES_RESOURCE_LOADER_LOADER_HPP
#define APP_CLIENT_MANAGEES_RESOURCE_LOADER_LOADER_HPP

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <common/extlibs/json/json.hpp>
#include <memory>
#include <string_view>

namespace client {
namespace managees {
namespace resource_detail {
template <class T> struct loader {};

template <> struct loader<common::extlibs::json> {
    static std::shared_ptr<common::extlibs::json> load(std::string_view path);
};

template <> struct loader<SDL_Surface> {
    static std::shared_ptr<SDL_Surface> load(std::string_view path);
};

template <> struct loader<Mix_Music> {
    static std::shared_ptr<Mix_Music> load(std::string_view path);
};

template <> struct loader<TTF_Font> {
    static std::shared_ptr<TTF_Font> load(std::string_view path, std::size_t point_size);
};
} // namespace resource_detail
} // namespace managees
} // namespace client

#endif
