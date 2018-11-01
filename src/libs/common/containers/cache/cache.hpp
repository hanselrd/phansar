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

#ifndef COMMON_CONTAINRS_CACHE_HPP
#define COMMON_CONTAINRS_CACHE_HPP

#include <optional>
#include <unordered_map>

namespace common {
namespace containers {
template <class K, class T> class cache {
public:
    std::optional<T> load(K key);
    void unload(K key);
    void store(K key, T data);
    void clear();

private:
    std::unordered_map<K, T> _cache;
};
} // namespace containers
} // namespace common

#include "cache.tpp"

#endif
