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

#include "loader.hpp"
#include <common/utils/assert/assert.hpp>
#include <fstream>

namespace client {
namespace managees {
namespace resource_detail {
std::shared_ptr<common::extlibs::json> loader<common::extlibs::json>::load(std::string_view path) {
    auto ifs = std::ifstream{std::string{path}};
    auto json = std::make_shared<common::extlibs::json>();
    ifs >> *json;
    return json;
}

std::shared_ptr<SDL_Surface> loader<SDL_Surface>::load(std::string_view path) {
    auto rw = SDL_RWFromFile(std::string{path}.c_str(), "rb");
    auto ptr = IMG_Load_RW(rw, true);
    ASSERT(ptr != nullptr);
    return std::shared_ptr<SDL_Surface>{ptr, &SDL_FreeSurface};
}

std::shared_ptr<Mix_Music> loader<Mix_Music>::load(std::string_view path) {
    auto rw = SDL_RWFromFile(std::string{path}.c_str(), "rb");
    auto ptr = Mix_LoadMUS_RW(rw, true);
    ASSERT(ptr != nullptr);
    return std::shared_ptr<Mix_Music>{ptr, &Mix_FreeMusic};
}

std::shared_ptr<TTF_Font> loader<TTF_Font>::load(std::string_view path, std::size_t point_size) {
    auto rw = SDL_RWFromFile(std::string{path}.c_str(), "rb");
    auto ptr = TTF_OpenFontRW(rw, true, point_size);
    ASSERT(ptr != nullptr);
    return std::shared_ptr<TTF_Font>{ptr, &TTF_CloseFont};
}
} // namespace resource_detail
} // namespace managees
} // namespace client
