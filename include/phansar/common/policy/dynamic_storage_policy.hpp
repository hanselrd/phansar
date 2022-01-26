#ifndef PHANSAR_COMMON_POLICY_DYNAMIC_STORAGE_POLICY_HPP
#define PHANSAR_COMMON_POLICY_DYNAMIC_STORAGE_POLICY_HPP

#include <memory>

namespace phansar::common::policy {
template <class T>
class dynamic_storage_policy {
public:
    template <class... Args>
    explicit dynamic_storage_policy(Args &&... _args);
    dynamic_storage_policy(const dynamic_storage_policy & _other);
    auto operator=(const dynamic_storage_policy & _other) -> dynamic_storage_policy &;
    dynamic_storage_policy(dynamic_storage_policy && _other) noexcept;
    auto operator=(dynamic_storage_policy && _other) noexcept -> dynamic_storage_policy &;
    virtual ~dynamic_storage_policy();

    auto operator*() const -> const T &;
    auto operator*() -> T &;
    auto operator->() const -> const T *;
    auto operator->() -> T *;

private:
    std::unique_ptr<T> m_storage{};
};
} // namespace phansar::common::policy

#include <phansar/common/policy/dynamic_storage_policy.inl>

#endif
