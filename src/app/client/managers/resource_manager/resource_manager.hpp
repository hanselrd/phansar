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

#ifndef CLIENT_MANAGERS_RESOURCE_MANAGER_HPP
#define CLIENT_MANAGERS_RESOURCE_MANAGER_HPP

#include <cstdint>
#include <memory>
#include <string_view>
#include <vector>

namespace client {
namespace managers {
namespace resource_manager {
namespace detail {
enum class resource_type { JSON, SDL_SURFACE, MIX_MUSIC, TTF_FONT };

void load(std::string_view path, resource_type rt);
std::shared_ptr<void> get(std::string_view path, resource_type rt);
} // namespace detail

template <class T> void load(std::string_view path);
template <class T> std::shared_ptr<T> get(std::string_view path);
} // namespace resource_manager
} // namespace managers
} // namespace client

#include "resource_manager.tpp"

#endif
