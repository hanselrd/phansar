#include <phansar/common/utility/pimpl.hpp>

namespace phansar::common::utility {
template <class T, class StoragePolicy>
template <class... Args>
pimpl<T, StoragePolicy>::pimpl(Args &&... _args)
    : m_storage_policy{std::forward<Args>(_args)...} {}

template <class T, class StoragePolicy>
pimpl<T, StoragePolicy>::pimpl(pimpl const & _other) = default;

template <class T, class StoragePolicy>
auto pimpl<T, StoragePolicy>::operator=(pimpl const & _other)
    -> pimpl<T, StoragePolicy> & = default;

template <class T, class StoragePolicy>
pimpl<T, StoragePolicy>::pimpl(pimpl && _other) noexcept = default;

template <class T, class StoragePolicy>
auto pimpl<T, StoragePolicy>::operator=(pimpl && _other) noexcept
    -> pimpl<T, StoragePolicy> & = default;

template <class T, class StoragePolicy>
pimpl<T, StoragePolicy>::~pimpl() = default;

template <class T, class StoragePolicy>
auto pimpl<T, StoragePolicy>::operator*() const -> const T & {
  return m_storage_policy.operator*();
}

template <class T, class StoragePolicy>
auto pimpl<T, StoragePolicy>::operator*() -> T & {
  return const_cast<T &>(static_cast<pimpl const &>(*this).operator*());
}

template <class T, class StoragePolicy>
auto pimpl<T, StoragePolicy>::operator->() const -> const T * {
  return m_storage_policy.operator->();
}

template <class T, class StoragePolicy>
auto pimpl<T, StoragePolicy>::operator->() -> T * {
  return const_cast<T *>(static_cast<pimpl const &>(*this).operator->());
}
} // namespace phansar::common::utility
