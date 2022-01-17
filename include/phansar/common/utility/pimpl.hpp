#ifndef PHANSAR_COMMON_UTILITY_PIMPL_HPP
#define PHANSAR_COMMON_UTILITY_PIMPL_HPP

#include <phansar/common/policy/dynamic_storage_policy.hpp>

namespace phansar::common::utility {
template <class T, class StoragePolicy = policy::dynamic_storage_policy<T>>
class pimpl {
public:
    template <class... Args>
    explicit pimpl(Args &&... _args);
    pimpl(const pimpl & _other);
    auto operator=(const pimpl & _other) -> pimpl &;
    pimpl(pimpl && _other) noexcept;
    auto operator=(pimpl && _other) noexcept -> pimpl &;
    virtual ~pimpl();

    auto operator*() const -> const T &;
    auto operator*() -> T &;
    auto operator->() const -> const T *;
    auto operator->() -> T *;

private:
    StoragePolicy m_storage_policy;
};

} // namespace phansar::common::utility

#include <phansar/common/utility/pimpl.inl>

#endif
