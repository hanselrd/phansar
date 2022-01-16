#include <phansar/common/utility/pimpl.hpp>

namespace phansar::common::utility {
template <class T, class StoragePolicy>
template <class... Args>
pimpl<T, StoragePolicy>::pimpl(Args &&... _args) : m_storage_policy{std::forward<Args>(_args)...} {}

PH_RULE_OF_5_TEMPLATE_DEFAULT(pimpl,
                              PH_PACK(template <class T, class StoragePolicy>),
                              T,
                              StoragePolicy);

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
