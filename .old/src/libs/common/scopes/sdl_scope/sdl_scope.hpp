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

#ifndef LIBS_COMMON_SCOPES_SDL_SCOPE_SDL_SCOPE_HPP
#define LIBS_COMMON_SCOPES_SDL_SCOPE_SDL_SCOPE_HPP

#include "../base_scope/base_scope.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
// #include <SDL2/SDL_net.h>
#include <SDL2/SDL_ttf.h>
#include <cstdint>

namespace common {
namespace scopes {
class sdl_scope : public detail::base_scope<sdl_scope> {
public:
    explicit sdl_scope(std::uint32_t flags);
    ~sdl_scope();
};

class sdl_image_scope : public detail::base_scope<sdl_image_scope> {
public:
    explicit sdl_image_scope(std::uint32_t flags);
    ~sdl_image_scope();
};

class sdl_mixer_scope : public detail::base_scope<sdl_mixer_scope> {
public:
    explicit sdl_mixer_scope(std::uint32_t flags);
    ~sdl_mixer_scope();
};

// class sdl_net_scope : public detail::base_scope<sdl_net_scope> {
// public:
//     sdl_net_scope();
//     ~sdl_net_scope();
// };

class sdl_ttf_scope : public detail::base_scope<sdl_ttf_scope> {
public:
    sdl_ttf_scope();
    ~sdl_ttf_scope();
};
} // namespace scopes
} // namespace common

#endif
