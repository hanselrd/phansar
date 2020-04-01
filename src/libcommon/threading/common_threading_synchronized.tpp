#include "common_threading_synchronized.hpp"
#include <functional>

namespace common::threading {
template <class T, class Mutex>
synchronized<T, Mutex>::proxy::proxy(T &obj, Mutex &mutex) : _obj_r{obj}, _mutex_r{mutex} {
}

template <class T, class Mutex> synchronized<T, Mutex>::proxy::~proxy() {
    _mutex_r.unlock();
}

template <class T, class Mutex> T &synchronized<T, Mutex>::proxy::operator*() const {
    return _obj_r;
}

template <class T, class Mutex> T *synchronized<T, Mutex>::proxy::operator->() const {
    return &_obj_r;
}

template <class T, class Mutex> T &synchronized<T, Mutex>::synchronized::proxy::get() const {
    return operator*();
}

template <class T, class Mutex>
template <class... Args>
synchronized<T, Mutex>::synchronized(Args &&... args) : _obj{std::forward<Args>(args)...} {
}

template <class T, class Mutex>
typename synchronized<T, Mutex>::proxy synchronized<T, Mutex>::lock() {
    _mutex.lock();
    return proxy{_obj, _mutex};
}

template <class T, class Mutex>
std::optional<typename synchronized<T, Mutex>::proxy> synchronized<T, Mutex>::try_lock() {
    if (_mutex.try_lock()) {
        return proxy{_obj, _mutex};
    } else {
        return std::nullopt;
    }
}
} // namespace common::threading
