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

namespace client {
namespace managers {
namespace resource_manager {
template <class T> std::optional<managees::resource<T>> get(std::string_view path) {
    auto res = detail::get(path);
    if (res != std::nullopt) {
        return std::any_cast<managees::resource<T>>(*res);
    }

    auto rsrc = managees::resource<T>{};
    rsrc.load(path);
    detail::store(path, std::make_any<managees::resource<T>>(rsrc));
    return rsrc;
}
} // namespace resource_manager
} // namespace managers
} // namespace client

#endif
