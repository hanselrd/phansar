#include <phansar/common/utility/pimpl.hpp>

namespace phansar::common::utility {
template <class T>
template <class... Args>
pimpl<T>::pimpl(Args &&... _args) : m_instance{new T{std::forward<Args>(_args)...}} {}

template <class T>
pimpl<T>::pimpl(const pimpl & _other)
    : m_instance{_other.m_instance ? new T{*_other.m_instance} : nullptr} {}

template <class T>
auto pimpl<T>::operator=(const pimpl & _other) -> pimpl & {
    if (this != &_other) {
        m_instance.reset(new T{*_other.m_instance});
    }
    return *this;
}

template <class T>
auto pimpl<T>::operator*() const -> const T & {
    return *m_instance.get();
}

template <class T>
auto pimpl<T>::operator*() -> T & {
    return const_cast<T &>(*const_cast<const pimpl *>(this)->operator*());
}

template <class T>
auto pimpl<T>::operator->() const -> const T * {
    return m_instance.get();
}

template <class T>
auto pimpl<T>::operator->() -> T * {
    return const_cast<T *>(const_cast<const pimpl *>(this)->operator->());
}
} // namespace phansar::common::utility
