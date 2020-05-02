#include <phansar/common/log.hpp>
#include <phansar/common/threading/thread_pool.hpp>

#include <memory>

namespace phansar::common::threading {
template <class F, class... Args>
void thread_pool::push_work(F && f, Args &&... args) {
    auto work = [f = std::forward<F>(f), ... args = std::forward<Args>(args)] {
        std::invoke(f, args...);
    };
    auto i = _index.fetch_add(1);

    for (auto n = std::size_t{0}; n < _threads.size(); ++n) {
        if (auto l = _queues[(i + n) % _threads.size()].try_lock(); l.has_value()) {
            l.value()->push(work);
            LOGT("Pushed work to worker queue {} ({})",
                 (i + n) % _threads.size(),
                 l.value()->size());
            return;
        }
    }

    auto l = _queues[i % _threads.size()].lock();
    l->push(work);
    LOGT("Pushed work to worker queue {} ({})", i % _threads.size(), l->size());
}

template <class F, class... Args, class R>
auto thread_pool::push_task(F && f, Args &&... args) -> std::future<R> {
    auto task = std::make_shared<std::packaged_task<R()>>(
        [f = std::forward<F>(f), ... args = std::forward<Args>(args)] {
            return std::invoke(f, args...);
        });
    auto fut = task->get_future();

    auto work = [task] { (*task)(); };
    auto i    = _index.fetch_add(1);

    for (auto n = std::size_t{0}; n < _threads.size(); ++n) {
        if (auto l = _queues[(i + n) % _threads.size()].try_lock(); l.has_value()) {
            l.value()->push(work);
            LOGT("Pushed task to worker queue {} ({})",
                 (i + n) % _threads.size(),
                 l.value()->size());
            return fut;
        }
    }

    auto l = _queues[i % _threads.size()].lock();
    l->push(work);
    LOGT("Pushed task to worker queue {} ({})", i % _threads.size(), l->size());
    return fut;
}
} // namespace phansar::common::threading
