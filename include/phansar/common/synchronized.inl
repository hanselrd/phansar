#include <phansar/common/synchronized.hpp>

namespace phansar::common {
template <class T, class ImplementationPolicy>
template <bool Writable>
struct synchronized<T, ImplementationPolicy>::proxy<Writable>::impl {
    T *                 obj;
    std::shared_mutex * mutex;
};

template <class T, class ImplementationPolicy>
template <bool Writable>
synchronized<T, ImplementationPolicy>::proxy<Writable>::proxy(T & _obj, std::shared_mutex & _mutex)
    : m_impl{&_obj, &_mutex} {}

template <class T, class ImplementationPolicy>
template <bool Writable>
synchronized<T, ImplementationPolicy>::proxy<Writable>::proxy(const proxy & _other) = default;

template <class T, class ImplementationPolicy>
template <bool Writable>
auto synchronized<T, ImplementationPolicy>::proxy<Writable>::operator=(const proxy & _other)
    -> synchronized<T, ImplementationPolicy>::proxy<Writable> &      = default;

template <class T, class ImplementationPolicy>
template <bool Writable>
synchronized<T, ImplementationPolicy>::proxy<Writable>::proxy(proxy && _other) noexcept
    : m_impl{std::exchange(_other.m_impl->obj, nullptr),
             std::exchange(_other.m_impl->mutex, nullptr)} {}

template <class T, class ImplementationPolicy>
template <bool Writable>
auto synchronized<T, ImplementationPolicy>::proxy<Writable>::operator=(proxy && _other) noexcept
    -> synchronized<T, ImplementationPolicy>::proxy<Writable> & {
    if (this != &_other) {
        if (m_impl->mutex != nullptr) {
            if constexpr (Writable) {
                m_impl->mutex->unlock();
            } else {
                m_impl->mutex->unlock_shared();
            }
        }

        m_impl->obj   = std::exchange(_other.m_impl->obj, nullptr);
        m_impl->mutex = std::exchange(_other.m_impl->mutex, nullptr);
    }

    return *this;
}

template <class T, class ImplementationPolicy>
template <bool Writable>
synchronized<T, ImplementationPolicy>::proxy<Writable>::~proxy() {
    if (m_impl->mutex != nullptr) {
        if constexpr (Writable) {
            m_impl->mutex->unlock();
        } else {
            m_impl->mutex->unlock_shared();
        }
    }
}

template <class T, class ImplementationPolicy>
template <bool Writable>
template <bool Writable2, class>
auto synchronized<T, ImplementationPolicy>::proxy<Writable>::get() -> T * {
    return m_impl->obj;
}

template <class T, class ImplementationPolicy>
template <bool Writable>
template <bool Writable2, class>
auto synchronized<T, ImplementationPolicy>::proxy<Writable>::operator*() -> T & {
    return *get();
}

template <class T, class ImplementationPolicy>
template <bool Writable>
template <bool Writable2, class>
auto synchronized<T, ImplementationPolicy>::proxy<Writable>::operator->() -> T * {
    return get();
}

template <class T, class ImplementationPolicy>
template <bool Writable>
template <bool Writable2, class>
auto synchronized<T, ImplementationPolicy>::proxy<Writable>::get() const -> const T * {
    return m_impl->obj;
}

template <class T, class ImplementationPolicy>
template <bool Writable>
template <bool Writable2, class>
auto synchronized<T, ImplementationPolicy>::proxy<Writable>::operator*() const -> const T & {
    return *get();
}

template <class T, class ImplementationPolicy>
template <bool Writable>
template <bool Writable2, class>
auto synchronized<T, ImplementationPolicy>::proxy<Writable>::operator->() const -> const T * {
    return get();
}

template <class T, class ImplementationPolicy>
struct synchronized<T, ImplementationPolicy>::impl {
    T                                  obj;
    std::unique_ptr<std::shared_mutex> mutex;
};

template <class T, class ImplementationPolicy>
template <class... Args>
synchronized<T, ImplementationPolicy>::synchronized(Args &&... _args)
    : m_impl{T{std::forward<Args>(_args)...}, std::make_unique<std::shared_mutex>()} {}

template <class T, class ImplementationPolicy>
synchronized<T, ImplementationPolicy>::synchronized(const synchronized & _other) = default;

template <class T, class ImplementationPolicy>
auto synchronized<T, ImplementationPolicy>::operator=(const synchronized & _other)
    -> synchronized<T, ImplementationPolicy> &      = default;

template <class T, class ImplementationPolicy>
synchronized<T, ImplementationPolicy>::synchronized(synchronized && _other) noexcept = default;

template <class T, class ImplementationPolicy>
auto synchronized<T, ImplementationPolicy>::operator=(synchronized && _other) noexcept
    -> synchronized<T, ImplementationPolicy> &      = default;

template <class T, class ImplementationPolicy>
synchronized<T, ImplementationPolicy>::~synchronized() = default;

template <class T, class ImplementationPolicy>
auto synchronized<T, ImplementationPolicy>::lock()
    -> synchronized<T, ImplementationPolicy>::proxy<true> {
    m_impl->mutex->lock();
    return proxy<true>{m_impl->obj, *m_impl->mutex};
}

template <class T, class ImplementationPolicy>
auto synchronized<T, ImplementationPolicy>::try_lock()
    -> std::optional<synchronized<T, ImplementationPolicy>::proxy<true>> {
    if (m_impl->mutex->try_lock()) {
        return proxy<true>{m_impl->obj, *m_impl->mutex};
    }

    return std::nullopt;
}

template <class T, class ImplementationPolicy>
auto synchronized<T, ImplementationPolicy>::lock_shared()
    -> synchronized<T, ImplementationPolicy>::proxy<false> {
    m_impl->mutex->lock_shared();
    return proxy<false>{m_impl->obj, *m_impl->mutex};
}

template <class T, class ImplementationPolicy>
auto synchronized<T, ImplementationPolicy>::try_lock_shared()
    -> std::optional<synchronized<T, ImplementationPolicy>::proxy<false>> {
    if (m_impl->mutex->try_lock_shared()) {
        return proxy<false>{m_impl->obj, *m_impl->mutex};
    }

    return std::nullopt;
}
} // namespace phansar::common
