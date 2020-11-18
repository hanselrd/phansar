#include <phansar/common/threading/synchronized.hpp>

namespace phansar::common::threading {
template <class T>
template <class Tag>
synchronized<T>::proxy<Tag>::proxy(T & _obj, std::shared_mutex & _mutex)
    : m_obj_p{&_obj}, m_mutex_p{&_mutex} {}

template <class T>
template <class Tag>
synchronized<T>::proxy<Tag>::proxy(proxy && _other) noexcept
    : m_obj_p{std::exchange(_other.m_obj_p, nullptr)}, m_mutex_p{std::exchange(_other.m_mutex_p,
                                                                               nullptr)} {}

template <class T>
template <class Tag>
auto synchronized<T>::proxy<Tag>::operator=(proxy && _other) noexcept
    -> synchronized<T>::proxy<Tag> & {
    if (this != &_other) {
        if (m_mutex_p != nullptr) {
            if constexpr (std::is_same_v<Tag, write_tag>) {
                m_mutex_p->unlock();
            } else if (std::is_same_v<Tag, read_tag>) {
                m_mutex_p->unlock_shared();
            }
        }
        m_obj_p   = std::exchange(_other.m_obj_p, nullptr);
        m_mutex_p = std::exchange(_other.m_mutex_p, nullptr);
    }
    return *this;
}

template <class T>
template <class Tag>
synchronized<T>::proxy<Tag>::~proxy() {
    if (m_mutex_p != nullptr) {
        if constexpr (std::is_same_v<Tag, write_tag>) {
            m_mutex_p->unlock();
        } else if (std::is_same_v<Tag, read_tag>) {
            m_mutex_p->unlock_shared();
        }
    }
}

template <class T>
template <class Tag>
template <class U>
[[nodiscard]] auto synchronized<T>::proxy<Tag>::get() const
    -> std::enable_if_t<std::is_same_v<U, write_tag>, T *> {
    return m_obj_p;
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
[[nodiscard]] auto synchronized<T>::proxy<Tag>::get() const
    -> std::enable_if_t<std::is_same_v<U, read_tag>, const T *> {
    return m_obj_p;
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
template <class... Args>
synchronized<T>::synchronized(Args &&... _args) : m_obj{std::forward<Args>(_args)...} {}

template <class T>
auto synchronized<T>::lock() -> synchronized<T>::proxy<write_tag> {
    m_mutex.lock();
    return proxy<write_tag>{m_obj, m_mutex};
}

template <class T>
auto synchronized<T>::try_lock() -> std::optional<synchronized<T>::proxy<write_tag>> {
    if (m_mutex.try_lock()) {
        return proxy<write_tag>{m_obj, m_mutex};
    }
    return std::nullopt;
}

template <class T>
auto synchronized<T>::lock_shared() -> synchronized<T>::proxy<read_tag> {
    m_mutex.lock_shared();
    return proxy<read_tag>{m_obj, m_mutex};
}

template <class T>
auto synchronized<T>::try_lock_shared() -> std::optional<synchronized<T>::proxy<read_tag>> {
    if (m_mutex.try_lock_shared()) {
        return proxy<read_tag>{m_obj, m_mutex};
    }
    return std::nullopt;
}
} // namespace phansar::common::threading
