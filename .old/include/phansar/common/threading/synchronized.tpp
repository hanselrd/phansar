#include <phansar/common/threading/synchronized.hpp>

namespace phansar::common::threading {
template <class T>
template <class Tag>
struct synchronized<T>::proxy<Tag>::impl {
    T *                 obj_p;
    std::shared_mutex * mutex_p;
};

template <class T>
template <class Tag>
synchronized<T>::proxy<Tag>::proxy(T & _obj, std::shared_mutex & _mutex) : m_impl{&_obj, &_mutex} {}

template <class T>
template <class Tag>
synchronized<T>::proxy<Tag>::proxy(proxy && _other) noexcept
    : m_impl{std::exchange(_other.m_impl->obj_p, nullptr),
             std::exchange(_other.m_impl->mutex_p, nullptr)} {}

template <class T>
template <class Tag>
auto synchronized<T>::proxy<Tag>::operator=(proxy && _other) noexcept
    -> synchronized<T>::proxy<Tag> & {
    if (this != &_other) {
        if (m_impl->mutex_p != nullptr) {
            if constexpr (std::is_same_v<Tag, write_tag>) {
                m_impl->mutex_p->unlock();
            } else if (std::is_same_v<Tag, read_tag>) {
                m_impl->mutex_p->unlock_shared();
            }
        }
        m_impl->obj_p   = std::exchange(_other.m_impl->obj_p, nullptr);
        m_impl->mutex_p = std::exchange(_other.m_impl->mutex_p, nullptr);
    }
    return *this;
}

template <class T>
template <class Tag>
synchronized<T>::proxy<Tag>::~proxy() {
    if (m_impl->mutex_p != nullptr) {
        if constexpr (std::is_same_v<Tag, write_tag>) {
            m_impl->mutex_p->unlock();
        } else if (std::is_same_v<Tag, read_tag>) {
            m_impl->mutex_p->unlock_shared();
        }
    }
}

template <class T>
template <class Tag>
template <class U>
[[nodiscard]] auto synchronized<T>::proxy<Tag>::get() const
    -> std::enable_if_t<std::is_same_v<U, write_tag>, T *> {
    return m_impl->obj_p;
}

template <class T>
template <class Tag>
template <class U>
auto synchronized<T>::proxy<Tag>::operator*() const
    -> std::enable_if_t<std::is_same_v<U, write_tag>, T &> {
    return *get();
}

template <class T>
template <class Tag>
template <class U>
auto synchronized<T>::proxy<Tag>::operator->() const
    -> std::enable_if_t<std::is_same_v<U, write_tag>, T *> {
    return get();
}

template <class T>
template <class Tag>
template <class U>
auto synchronized<T>::proxy<Tag>::get() const
    -> std::enable_if_t<std::is_same_v<U, read_tag>, const T *> {
    return m_impl->obj_p;
}

template <class T>
template <class Tag>
template <class U>
auto synchronized<T>::proxy<Tag>::operator*() const
    -> std::enable_if_t<std::is_same_v<U, read_tag>, const T &> {
    return *get();
}

template <class T>
template <class Tag>
template <class U>
auto synchronized<T>::proxy<Tag>::operator->() const
    -> std::enable_if_t<std::is_same_v<U, read_tag>, const T *> {
    return get();
}

template <class T>
struct synchronized<T>::impl {
    T                                  obj;
    std::unique_ptr<std::shared_mutex> mutex;
};

template <class T>
template <class... Args>
synchronized<T>::synchronized(Args &&... _args)
    : m_impl{std::forward<Args>(_args)..., std::make_unique<std::shared_mutex>()} {}

template <class T>
auto synchronized<T>::lock() -> synchronized<T>::proxy<write_tag> {
    m_impl->mutex->lock();
    return proxy<write_tag>{m_impl->obj, *m_impl->mutex};
}

template <class T>
auto synchronized<T>::try_lock() -> std::optional<synchronized<T>::proxy<write_tag>> {
    if (m_impl->mutex->try_lock()) {
        return proxy<write_tag>{m_impl->obj, *m_impl->mutex};
    }
    return std::nullopt;
}

template <class T>
auto synchronized<T>::lock_shared() -> synchronized<T>::proxy<read_tag> {
    m_impl->mutex->lock_shared();
    return proxy<read_tag>{m_impl->obj, *m_impl->mutex};
}

template <class T>
auto synchronized<T>::try_lock_shared() -> std::optional<synchronized<T>::proxy<read_tag>> {
    if (m_impl->mutex->try_lock_shared()) {
        return proxy<read_tag>{m_impl->obj, *m_impl->mutex};
    }
    return std::nullopt;
}
} // namespace phansar::common::threading
