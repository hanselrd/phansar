#ifndef PHANSAR_COMMON_THREADING_THREAD_POOL_HPP
#define PHANSAR_COMMON_THREADING_THREAD_POOL_HPP

#include <phansar/common/threading/synchronized.hpp>

#include <atomic>
#include <cstddef>
#include <functional>
#include <future>
#include <queue>
#include <thread>
#include <vector>

namespace phansar::common::threading {
class thread_pool {
    using work_function = std::function<void()>;
    using sync_queue    = synchronized<std::queue<work_function>>;

public:
    explicit thread_pool(std::size_t nthreads = std::thread::hardware_concurrency());
    thread_pool(const thread_pool &) = delete;
    auto operator=(const thread_pool &) -> thread_pool & = delete;
    thread_pool(thread_pool &&)                          = delete;
    auto operator=(thread_pool &&) -> thread_pool & = delete;
    ~thread_pool();

    template <class F, class... Args>
    void push_work(F && f, Args &&... args);
    template <class F, class... Args, class R = std::invoke_result_t<F, Args...>>
    auto push_task(F && f, Args &&... args) -> std::future<R>;
    void wait_done();

private:
    std::vector<sync_queue>  _queues;
    std::vector<std::thread> _threads;
    std::atomic_uint64_t     _index   = 0;
    volatile bool            _running = true;
};
} // namespace phansar::common::threading

#include <phansar/common/threading/detail/thread_pool.tpp>

#endif
