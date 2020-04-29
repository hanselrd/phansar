#include <phansar/common/log.hpp>
#include <phansar/common/threading/thread_pool.hpp>

#include <phansar/vendor/rangev3.hpp>

namespace phansar::common::threading {
thread_pool::thread_pool(std::size_t nthreads) : _queues{nthreads} {
    for (auto i = std::size_t{0}; i < nthreads; ++i) {
        _threads.emplace_back([this, i] {
            LOGD("Worker {} initialized", i);
            while (_running) {
                for (auto n = std::size_t{0}; n < _threads.size(); ++n) {
                    if (auto l = _queues[(i + n) % _threads.size()].try_lock();
                        l.has_value() && ! l.value()->empty()) {
                        l.value()->front()();
                        l.value()->pop();
                        LOGT("Worker {} executed from queue {} ({})",
                             i,
                             (i + n) % _threads.size(),
                             l.value()->size());
                    }
                }

                if (auto l = _queues[i].lock(); ! l->empty()) {
                    l->front()();
                    l->pop();
                    LOGT("Worker {0} executed from queue {0} ({1})", i, l->size());
                }
            }
            LOGD("Worker {} shutdown", i);
        });
    }
}

thread_pool::~thread_pool() {
    _running = false;

    ranges::for_each(_threads, [](auto & t) {
        if (t.joinable()) {
            t.join();
        }
    });
}

void thread_pool::wait_done() {
    while (ranges::accumulate(_queues, 0, [](std::size_t sum, auto & q) {
               return sum + q.lock()->size();
           }) > 0) {
    }
}
} // namespace phansar::common::threading
