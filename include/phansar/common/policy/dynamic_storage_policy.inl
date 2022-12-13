#include <phansar/common/policy/dynamic_storage_policy.hpp>

namespace phansar::common::policy {
template <class T>
template <class... Args>
dynamic_storage_policy<T>::dynamic_storage_policy(Args &&... _args)
    : m_storage{new T{std::forward<Args>(_args)...}} {}

template <class T>
dynamic_storage_policy<T>::dynamic_storage_policy(const dynamic_storage_policy & _other)
    : m_storage{_other.m_storage ? new T{*_other.m_storage} : nullptr} {}

template <class T>
auto dynamic_storage_policy<T>::operator=(const dynamic_storage_policy & _other)
    -> dynamic_storage_policy<T> & {
    if (this != &_other) {
        m_storage.reset(new T{*_other.m_storage});
    }

    return *this;
}

template <class T>
dynamic_storage_policy<T>::dynamic_storage_policy(dynamic_storage_policy && _other) noexcept =
    default;

template <class T>
auto dynamic_storage_policy<T>::operator=(dynamic_storage_policy && _other) noexcept
    -> dynamic_storage_policy<T> & = default;

template <class T>
dynamic_storage_policy<T>::~dynamic_storage_policy() = default;

template <class T>
auto dynamic_storage_policy<T>::operator*() const -> const T & {
    return *m_storage.get();
}

template <class T>
auto dynamic_storage_policy<T>::operator*() -> T & {
    return const_cast<T &>(dynamic_cast<const dynamic_storage_policy &>(*this).operator*());
}

template <class T>
auto dynamic_storage_policy<T>::operator->() const -> const T * {
    return m_storage.get();
}

template <class T>
auto dynamic_storage_policy<T>::operator->() -> T * {
    return const_cast<T *>(dynamic_cast<const dynamic_storage_policy &>(*this).operator->());
}
} // namespace phansar::common::policy
