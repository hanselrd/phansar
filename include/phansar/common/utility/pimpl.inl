#include <phansar/common/utility/pimpl.hpp>

namespace phansar::common::utility {
template <class T, class StoragePolicy>
template <class... Args>
pimpl<T, StoragePolicy>::pimpl(Args &&... _args) : m_storage_policy{std::forward<Args>(_args)...} {}

template <class T, class StoragePolicy>
PH_COPY_CONSTRUCTOR_DEFAULT(pimpl, T, StoragePolicy);

template <class T, class StoragePolicy>
PH_COPY_ASSIGNMENT_DEFAULT(pimpl, T, StoragePolicy);

template <class T, class StoragePolicy>
PH_MOVE_CONSTRUCTOR_DEFAULT(pimpl, T, StoragePolicy);

template <class T, class StoragePolicy>
PH_MOVE_ASSIGNMENT_DEFAULT(pimpl, T, StoragePolicy);

template <class T, class StoragePolicy>
PH_DESTRUCTOR_DEFAULT(pimpl, T, StoragePolicy);

template <class T, class StoragePolicy>
auto pimpl<T, StoragePolicy>::operator*() const -> const T & {
    return m_storage_policy.operator*();
}

template <class T, class StoragePolicy>
auto pimpl<T, StoragePolicy>::operator*() -> T & {
    return const_cast<T &>(static_cast<const pimpl &>(*this).operator*());
}

template <class T, class StoragePolicy>
auto pimpl<T, StoragePolicy>::operator->() const -> const T * {
    return m_storage_policy.operator->();
}

template <class T, class StoragePolicy>
auto pimpl<T, StoragePolicy>::operator->() -> T * {
    return const_cast<T *>(static_cast<const pimpl &>(*this).operator->());
}
} // namespace phansar::common::utility
