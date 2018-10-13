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

#ifndef COMMON_CONTAINERS_EVENT_QUEUE_TPP
#define COMMON_CONTAINERS_EVENT_QUEUE_TPP

#include "event_queue.hpp"

namespace common {
namespace containers {
template <class E, class T>
template <class... Args, class>
event_queue<E, T>::event_queue(Args &&... args) : _whitelist{std::forward<Args>(args)...} {
}

template <class E, class T> void event_queue<E, T>::event(const E &e, T t) {
    if (_whitelist.size() != 0) {
        auto found = bool{false};
        for (auto &w : _whitelist) {
            if (w == t) {
                found = true;
            }
        }
        if (!found) {
            return;
        }
    }

    _queue.emplace(e);
}

template <class E, class T> void event_queue<E, T>::subscribe(subscribe_function f) {
    _subscribers.emplace_back(std::move(f));
}

template <class E, class T> void event_queue<E, T>::update() {
    while (_queue.size() > 0) {
        auto e = _queue.front();
        _queue.pop();

        for (const auto &s : _subscribers) {
            s(e);
        }
    }
}
} // namespace containers
} // namespace common

#endif
