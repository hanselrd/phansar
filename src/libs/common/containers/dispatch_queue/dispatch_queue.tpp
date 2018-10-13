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

#ifndef COMMON_CONTAINERS_DISPATCH_QUEUE_TPP
#define COMMON_CONTAINERS_DISPATCH_QUEUE_TPP

#include "dispatch_queue.hpp"
#include <memory>

namespace common {
namespace containers {
template <class F, class... Args, class R>
std::future<R> dispatch_queue::dispatch(F &&f, Args &&... args) {
    auto lock = std::unique_lock{_mutex};
    auto task = std::make_shared<std::packaged_task<R()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    auto fut = task->get_future();
    _queue.emplace([task = std::move(task)] { (*task)(); });

    // manually unlock before notifying to avoid waking up
    // waiting threads only to block again
    lock.unlock();
    _cv.notify_all();

    return fut;
}
} // namespace containers
} // namespace common

#endif
