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

#include "dispatch_queue.hpp"
#include "log.hpp"

namespace common {
namespace core {
dispatch_queue::dispatch_queue(std::size_t count) : _threads(count) {
    for (std::size_t i = 0; i < _threads.size(); ++i) {
        _threads[i] = std::thread([this, i] {
            LOGI << "Worker " << i << " initialized";
            _thread_handler();
            LOGI << "Worker " << i << " shutdown";
        });
    }
}

dispatch_queue::~dispatch_queue() {
    _running = false;
    _cv.notify_all();

    for (auto &t : _threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    LOGI << "Workers joined";
}

void dispatch_queue::dispatch(const job &j) {
    std::unique_lock<std::mutex> lock(_mutex);
    _queue.push(j);

    // manually unlock before notifying to avoid waking up
    // waiting threads only to block again
    lock.unlock();
    _cv.notify_all();
}

void dispatch_queue::dispatch(job &&j) {
    std::unique_lock<std::mutex> lock(_mutex);
    _queue.push(std::move(j));

    // manually unlock before notifying to avoid waking up
    // waiting threads only to block again
    lock.unlock();
    _cv.notify_all();
}

void dispatch_queue::_thread_handler() {
    std::unique_lock<std::mutex> lock(_mutex);

    do {
        // wait until there are queued jobs or _running is false
        _cv.wait(lock, [this] { return (_queue.size() > 0) || !_running; });

        // after waiting, we own the lock
        if ((_queue.size() > 0) && _running) {
            auto job = std::move(_queue.front());
            _queue.pop();

            // unlock now since we're done with the queue
            lock.unlock();
            job();
            LOGD << "Job completed";
            lock.lock();
        }
    } while (_running);
}
} // namespace core
} // namespace common
