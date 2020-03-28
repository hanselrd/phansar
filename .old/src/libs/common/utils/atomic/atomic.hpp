/**
 *  This file is part of Phansar.
 *
 *  Copyright (C) 2019  Hansel De La Cruz
 *
 *  Phansar is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Phansar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with Phansar.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBS_COMMON_UTILS_ATOMIC_ATOMIC_HPP
#define LIBS_COMMON_UTILS_ATOMIC_ATOMIC_HPP

#include <atomic>

namespace common::utils::atomic {
template <class T> inline T fetch_add(std::atomic<T> &shared, T val);

template <class T> inline T fetch_sub(std::atomic<T> &shared, T val);

template <class T> inline T fetch_mult(std::atomic<T> &shared, T val);

template <class T> inline T fetch_div(std::atomic<T> &shared, T val);

template <class T> inline T fetch_mod(std::atomic<T> &shared, T val);

template <class T> inline T fetch_and(std::atomic<T> &shared, T val);

template <class T> inline T fetch_or(std::atomic<T> &shared, T val);

template <class T> inline T fetch_xor(std::atomic<T> &shared, T val);
} // namespace common::utils::atomic

#include "atomic.tpp"

#endif
