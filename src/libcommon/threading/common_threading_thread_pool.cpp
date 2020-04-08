#include "common_threading_thread_pool.hpp"
#include "common_log.hpp"

namespace common::threading {
thread_pool::thread_pool(std::size_t nthreads) : _queues{nthreads} {
    for (auto i = std::size_t{0}; i < nthreads; ++i) {
        _threads.emplace_back([this, i] {
            LOGD("Worker {} initialized", i);
            while (_running) {
                for (auto n = std::size_t{0}; n < _threads.size(); ++n) {
                    if (auto l = _queues[(i + n) % _threads.size()].try_lock();
                        l.has_value() && !l.value()->empty()) {
                        l.value()->front()();
                        l.value()->pop();
                        LOGD("Worker {} executed from queue {} ({})",
                             i,
                             (i + n) % _threads.size(),
                             l.value()->size());
                    }
                }

                if (auto l = _queues[i].lock(); !l->empty()) {
                    l->front()();
                    l->pop();
                    LOGD("Worker {} executed from queue {} ({})", i, i, l->size());
                }
            }
            LOGD("Worker {} shutdown", i);
        });
    }
}

thread_pool::~thread_pool() {
    _running = false;

    for (auto &t : _threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}

void thread_pool::wait_done() {
    auto nwork = std::size_t{0};
    while (true) {
        for (auto &q : _queues) {
            nwork += q.lock()->size();
        }

        if (nwork > 0) {
            nwork = 0;
        } else {
            return;
        }
    }
}
} // namespace common::threading
