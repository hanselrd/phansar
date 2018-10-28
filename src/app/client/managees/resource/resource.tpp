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

#ifndef CLIENT_MANAGEES_RESOURCE_TPP
#define CLIENT_MANAGEES_RESOURCE_TPP

#include "loader/loader.hpp"
#include "resource.hpp"

namespace client {
namespace managees {
template <class T>
template <class... Args>
void resource<T>::load(std::string_view path, Args &&... args) {
    _res = std::shared_ptr<T>{resource_detail::loader<T>::load(path, std::forward<Args>(args)...)};
}

template <class T> template <class... Args> void resource<T>::store(T *res, Args &&... args) {
    _res = std::shared_ptr<T>{res, std::forward<Args>(args)...};
}

template <class T> T *resource<T>::get() const {
    return _res.get();
}
} // namespace managees
} // namespace client

#endif
