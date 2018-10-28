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

#ifndef COMMON_CONTAINERS_CACHE_TPP
#define COMMON_CONTAINERS_CACHE_TPP

#include "cache.hpp"

namespace common {
namespace containers {
template <class K, class T> std::optional<T> cache<K, T>::load(K key) {
    if (_cache.count(key) == 0) {
        return std::nullopt;
    }
    return _cache[key];
}

template <class K, class T> void cache<K, T>::store(K key, T data) {
    _cache[key] = data;
}
} // namespace containers
} // namespace common

#endif
