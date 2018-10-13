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

#ifndef CLIENT_MANAGERS_RESOURCE_MANAGER_TPP
#define CLIENT_MANAGERS_RESOURCE_MANAGER_TPP

#include "resource_manager.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <common/extlibs/json/json.hpp>
#include <type_traits>
#include <typeinfo>

namespace client {
namespace managers {
namespace resource_manager {
template <class T> void load(std::string_view path) {
    using U = std::shared_ptr<T>;

    static_assert(std::is_same<U, std::shared_ptr<common::extlibs::json>>::value ||
                      std::is_same<U, std::shared_ptr<SDL_Surface>>::value ||
                      std::is_same<U, std::shared_ptr<Mix_Music>>::value ||
                      std::is_same<U, std::shared_ptr<TTF_Font>>::value,
                  "T must be a resource type");

    if (typeid(U) == typeid(std::shared_ptr<common::extlibs::json>)) {
        detail::load(path, detail::resource_type::JSON);
    } else if (typeid(U) == typeid(std::shared_ptr<SDL_Surface>)) {
        detail::load(path, detail::resource_type::SDL_SURFACE);
    } else if (typeid(U) == typeid(std::shared_ptr<Mix_Music>)) {
        detail::load(path, detail::resource_type::MIX_MUSIC);
    } else if (typeid(U) == typeid(std::shared_ptr<TTF_Font>)) {
        detail::load(path, detail::resource_type::TTF_FONT);
    }
}

template <class T> std::shared_ptr<T> get(std::string_view path) {
    using U = std::shared_ptr<T>;

    static_assert(std::is_same<U, std::shared_ptr<common::extlibs::json>>::value ||
                      std::is_same<U, std::shared_ptr<SDL_Surface>>::value ||
                      std::is_same<U, std::shared_ptr<Mix_Music>>::value ||
                      std::is_same<U, std::shared_ptr<TTF_Font>>::value,
                  "T must be a resource type");

    if (typeid(U) == typeid(std::shared_ptr<common::extlibs::json>)) {
        return std::static_pointer_cast<T>(detail::get(path, detail::resource_type::JSON));
    } else if (typeid(U) == typeid(std::shared_ptr<SDL_Surface>)) {
        return std::static_pointer_cast<T>(detail::get(path, detail::resource_type::SDL_SURFACE));
    } else if (typeid(U) == typeid(std::shared_ptr<Mix_Music>)) {
        return std::static_pointer_cast<T>(detail::get(path, detail::resource_type::MIX_MUSIC));
    } else if (typeid(U) == typeid(std::shared_ptr<TTF_Font>)) {
        return std::static_pointer_cast<T>(detail::get(path, detail::resource_type::TTF_FONT));
    }

    return U{};
}
} // namespace resource_manager
} // namespace managers
} // namespace client

#endif
