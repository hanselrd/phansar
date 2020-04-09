#include "common_threading_synchronized.hpp"
#include <functional>

namespace common::threading {
template <class T, class Mutex>
synchronized<T, Mutex>::proxy::proxy(T & obj, Mutex & mutex) : _obj_p{&obj}, _mutex_p{&mutex} {}

template <class T, class Mutex>
synchronized<T, Mutex>::proxy::proxy(proxy && other) noexcept
    : _obj_p{std::exchange(other._obj_p, nullptr)}, _mutex_p{
                                                        std::exchange(other._mutex_p, nullptr)} {}

template <class T, class Mutex>
auto synchronized<T, Mutex>::proxy::operator=(proxy && other) noexcept ->
    typename synchronized<T, Mutex>::proxy & {
    if (this != &other) {
        std::exchange(other._obj_p, nullptr);
        std::exchange(other._mutex_p, nullptr);
    }
    return *this;
}

template <class T, class Mutex>
synchronized<T, Mutex>::proxy::~proxy() {
    if (_mutex_p) {
        _mutex_p->unlock();
    }
}

template <class T, class Mutex>
auto synchronized<T, Mutex>::proxy::operator*() const -> T & {
    return *_obj_p;
}

template <class T, class Mutex>
auto synchronized<T, Mutex>::proxy::operator-> () const -> T * {
    return _obj_p;
}

template <class T, class Mutex>
auto synchronized<T, Mutex>::synchronized::proxy::get() const -> T & {
    return operator*();
}

template <class T, class Mutex>
template <class... Args>
synchronized<T, Mutex>::synchronized(Args &&... args) : _obj{std::forward<Args>(args)...} {}

template <class T, class Mutex>
auto synchronized<T, Mutex>::lock() -> typename synchronized<T, Mutex>::proxy {
    _mutex.lock();
    return proxy{_obj, _mutex};
}

template <class T, class Mutex>
auto synchronized<T, Mutex>::try_lock() -> std::optional<typename synchronized<T, Mutex>::proxy> {
    if (_mutex.try_lock()) {
        return proxy{_obj, _mutex};
    }
    return std::nullopt;
}
} // namespace common::threading
