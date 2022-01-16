#ifndef PHANSAR_COMMON_UTILITY_PIMPL_HPP
#define PHANSAR_COMMON_UTILITY_PIMPL_HPP

#include <phansar/common/policy/dynamic_storage_policy.hpp>
#include <phansar/common/utility/rule_of_n.hpp>

namespace phansar::common::utility {
template <class T, class StoragePolicy = policy::dynamic_storage_policy<T>>
class pimpl {
public:
    template <class... Args>
    explicit pimpl(Args &&... _args);
    PH_RULE_OF_5(pimpl);

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
