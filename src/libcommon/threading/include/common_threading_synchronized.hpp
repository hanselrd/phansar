#ifndef LIBCOMMON_THREADING_INCLUDE_COMMON_THREADING_SYNCHRONIZED_HPP
#define LIBCOMMON_THREADING_INCLUDE_COMMON_THREADING_SYNCHRONIZED_HPP

#include <mutex>
#include <optional>

namespace common::threading {
template <class T, class Mutex = std::mutex>
class synchronized {
public:
    class proxy {
        friend class synchronized;

    public:
        proxy(const proxy &) = delete;
        auto operator=(const proxy &) -> proxy & = delete;
        proxy(proxy && other) noexcept;
        auto operator=(proxy && other) noexcept -> proxy &;
        ~proxy();

        auto               operator*() const -> T &;
        auto               operator-> () const -> T *;
        [[nodiscard]] auto get() const -> T &;

    private:
        proxy(T & obj, Mutex & mutex);

        T *     _obj_p;
        Mutex * _mutex_p;
    };

    template <class... Args>
    explicit synchronized(Args &&... args);

    auto lock() -> proxy;
    auto try_lock() -> std::optional<proxy>;

private:
    T     _obj;
    Mutex _mutex;
};
} // namespace common::threading

#include "../common_threading_synchronized.tpp"

#endif
