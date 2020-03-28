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

#ifndef LIBS_COMMON_CONTAINERS_DISPATCH_QUEUE_DISPATCH_QUEUE_HPP
#define LIBS_COMMON_CONTAINERS_DISPATCH_QUEUE_DISPATCH_QUEUE_HPP

#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <type_traits>
#include <vector>

namespace common {
namespace containers {
class dispatch_queue {
public:
    explicit dispatch_queue(std::size_t count = 1);
    dispatch_queue(const dispatch_queue &) = delete;
    dispatch_queue &operator=(const dispatch_queue &) = delete;
    dispatch_queue(dispatch_queue &&) = delete;
    dispatch_queue &operator=(dispatch_queue &&) = delete;
    ~dispatch_queue();

    template <class F,
              class... Args,
              class R = std::invoke_result_t<std::decay_t<F>, std::decay_t<Args>...>>
    std::future<R> dispatch(F &&f, Args &&... args);

private:
    void _thread_handler();

    std::vector<std::thread> _threads;
    std::queue<std::function<void()>> _queue;
    std::condition_variable _cv;
    std::mutex _mutex;
    volatile bool _running = true;
};
} // namespace containers
} // namespace common

#include "dispatch_queue.tpp"

#endif
