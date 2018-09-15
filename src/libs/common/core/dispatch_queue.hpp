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

#ifndef COMMON_CORE_DISPATCH_QUEUE_HPP
#define COMMON_CORE_DISPATCH_QUEUE_HPP

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace common {
namespace core {
class dispatch_queue {
    using job = std::function<void(void)>;

public:
    explicit dispatch_queue(std::size_t count = 1);
    ~dispatch_queue();

    void dispatch(const job &j);
    void dispatch(job &&j);

    dispatch_queue(const dispatch_queue &) = delete;
    dispatch_queue &operator=(const dispatch_queue &) = delete;
    dispatch_queue(dispatch_queue &&) = delete;
    dispatch_queue &operator=(dispatch_queue &&) = delete;

private:
    void _thread_handler();

    std::vector<std::thread> _threads;
    std::queue<job> _queue;
    std::condition_variable _cv;
    std::mutex _mutex;
    volatile bool _running = true;
};
} // namespace core
} // namespace common

#endif
