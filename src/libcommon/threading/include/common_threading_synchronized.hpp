#ifndef LIBCOMMON_THREADING_INCLUDE_COMMON_THREADING_SYNCHRONIZED_HPP
#define LIBCOMMON_THREADING_INCLUDE_COMMON_THREADING_SYNCHRONIZED_HPP

#include <mutex>
#include <optional>

namespace common::threading {
template <class T, class Mutex = std::mutex> class synchronized {
public:
    class proxy {
        friend class synchronized;

    public:
        proxy() = delete;
        proxy(const proxy &) = delete;
        ~proxy();
        T &operator*() const;
        T *operator->() const;
        T &get() const;

    private:
        explicit proxy(T &obj, Mutex &mutex);

        T &_obj_r;
        Mutex &_mutex_r;
    };

    template <class... Args> synchronized(Args &&... args);
    proxy lock();
    std::optional<proxy> try_lock();

private:
    T _obj;
    Mutex _mutex;
};
} // namespace common::threading

#include "../common_threading_synchronized.tpp"

#endif
