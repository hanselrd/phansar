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

#include "resource_manager.hpp"
#include <common/containers/cache/cache.hpp>
#include <string>

namespace client {
namespace managers {
namespace resource_manager {
namespace {
auto _cache = common::containers::cache<std::string, std::any>{};
} // namespace

namespace detail {
void store(std::string_view path, std::any res) {
    _cache.store(std::string{path}, res);
}

std::optional<std::any> get(std::string_view path) {
    return _cache.load(std::string{path});
}
} // namespace detail
} // namespace resource_manager
} // namespace managers
} // namespace client
