#ifndef LIBCOMMON_THREADING_INCLUDE_COMMON_THREADING_THREAD_POOL_HPP
#define LIBCOMMON_THREADING_INCLUDE_COMMON_THREADING_THREAD_POOL_HPP

#include "common_containers.hpp"
#include "common_threading_synchronized.hpp"
#include <atomic>
#include <functional>
#include <future>
#include <thread>

namespace common::threading {
class thread_pool {
    using work_function = std::function<void()>;

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
    containers::vector<synchronized<containers::queue<work_function>>> _queues;
    containers::vector<std::thread>                                    _threads;
    std::atomic_uint64_t                                               _index   = 0;
    volatile bool                                                      _running = true;
};
} // namespace common::threading

#include "../common_threading_thread_pool.tpp"

#endif
