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

#ifndef COMMON_UTILS_ATOMIC_TPP
#define COMMON_UTILS_ATOMIC_TPP

#include "../assert/assert.hpp"
#include "atomic.hpp"

namespace common::utils::atomic {
namespace detail {
template <class T, class F> inline T cas_loop(std::atomic<T> &shared, F &&f) {
    ASSERT(shared.is_always_lock_free);
    ASSERT(shared.is_lock_free());
    T old_val = shared.load();
    T new_val;
    do {
        new_val = f(old_val);
    } while (!shared.compare_exchange_weak(old_val, new_val));

    return old_val;
}
} // namespace detail

template <class T> inline T fetch_add(std::atomic<T> &shared, T val) {
    return detail::cas_loop(shared, [val](auto old_val) { return old_val + val; });
}

template <class T> inline T fetch_sub(std::atomic<T> &shared, T val) {
    return detail::cas_loop(shared, [val](auto old_val) { return old_val - val; });
}

template <class T> inline T fetch_mult(std::atomic<T> &shared, T val) {
    return detail::cas_loop(shared, [val](auto old_val) { return old_val * val; });
}

template <class T> inline T fetch_div(std::atomic<T> &shared, T val) {
    return detail::cas_loop(shared, [val](auto old_val) { return old_val / val; });
}

template <class T> inline T fetch_mod(std::atomic<T> &shared, T val) {
    return detail::cas_loop(shared, [val](auto old_val) { return old_val % val; });
}

template <class T> inline T fetch_and(std::atomic<T> &shared, T val) {
    return detail::cas_loop(shared, [val](auto old_val) { return old_val & val; });
}

template <class T> inline T fetch_or(std::atomic<T> &shared, T val) {
    return detail::cas_loop(shared, [val](auto old_val) { return old_val | val; });
}

template <class T> inline T fetch_xor(std::atomic<T> &shared, T val) {
    return detail::cas_loop(shared, [val](auto old_val) { return old_val ^ val; });
}
} // namespace common::utils::atomic

#endif
