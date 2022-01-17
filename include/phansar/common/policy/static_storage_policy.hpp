#ifndef PHANSAR_COMMON_POLICY_STATIC_STORAGE_POLICY_HPP
#define PHANSAR_COMMON_POLICY_STATIC_STORAGE_POLICY_HPP

#include <cstddef>
#include <type_traits>

namespace phansar::common::policy {
template <class T, std::size_t Size, std::size_t Align>
class static_storage_policy {
public:
    template <class... Args>
    explicit static_storage_policy(Args &&... _args);
    static_storage_policy(const static_storage_policy & _other);
    auto operator=(const static_storage_policy & _other) -> static_storage_policy &;
    static_storage_policy(static_storage_policy && _other) noexcept;
    auto operator=(static_storage_policy && _other) noexcept -> static_storage_policy &;
    virtual ~static_storage_policy();

    auto operator*() const -> const T &;
    auto operator*() -> T &;
    auto operator->() const -> const T *;
    auto operator->() -> T *;

private:
    std::aligned_storage_t<Size, Align> m_storage;
    bool                                m_valid = true;
};
} // namespace phansar::common::policy

#include <phansar/common/policy/static_storage_policy.inl>

#endif
