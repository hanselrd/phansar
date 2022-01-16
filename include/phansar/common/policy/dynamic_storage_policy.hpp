#ifndef PHANSAR_COMMON_POLICY_DYNAMIC_STORAGE_POLICY_HPP
#define PHANSAR_COMMON_POLICY_DYNAMIC_STORAGE_POLICY_HPP

#include <phansar/common/utility/rule_of_n.hpp>
#include <memory>

namespace phansar::common::policy {
template <class T>
class dynamic_storage_policy {
public:
    template <class... Args>
    explicit dynamic_storage_policy(Args &&... _args);
    PH_RULE_OF_5(dynamic_storage_policy);

    auto operator*() const -> const T &;
    auto operator*() -> T &;
    auto operator->() const -> const T *;
    auto operator->() -> T *;

private:
    std::unique_ptr<T> m_storage;
};
} // namespace phansar::common::policy

#include <phansar/common/policy/dynamic_storage_policy.inl>

#endif
