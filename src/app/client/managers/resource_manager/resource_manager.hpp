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

#include "../../managees/resource/resource.hpp"
#include <any>
#include <optional>
#include <string_view>

namespace client {
namespace managers {
namespace resource_manager {
namespace detail {
void store(std::string_view path, std::any res);
std::optional<std::any> get(std::string_view path);
} // namespace detail

void init();
template <class T, class... Args> void load(std::string_view path, Args &&... args);
template <class T> void store(std::string_view path, managees::resource<T> res);
template <class T> std::optional<managees::resource<T>> get(std::string_view path);
} // namespace resource_manager
} // namespace managers
} // namespace client

#include "resource_manager.tpp"

#endif
