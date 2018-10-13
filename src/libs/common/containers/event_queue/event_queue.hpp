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

#ifndef COMMON_CONTAINERS_EVENT_QUEUE_HPP
#define COMMON_CONTAINERS_EVENT_QUEUE_HPP

#include <functional>
#include <mutex>
#include <queue>
#include <type_traits>
#include <vector>

namespace common {
namespace containers {
template <class E, class T> class event_queue {
    static_assert(std::is_enum_v<T> || std::is_integral_v<T>);

    using subscribe_function = std::function<void(const E &)>;

public:
    template <class... Args,
              class = std::void_t<std::enable_if_t<std::is_convertible_v<Args, T>>...>>
    explicit event_queue(Args &&... args);

    void event(const E &e, T t);
    void subscribe(subscribe_function f);
    void update();

private:
    std::vector<subscribe_function> _subscribers;
    std::vector<T> _whitelist;
    std::queue<E> _queue;
};
} // namespace containers
} // namespace common

#include "event_queue.tpp"

#endif
