#ifndef PHANSAR_COMMON_SYNCHRONIZED_HPP
#define PHANSAR_COMMON_SYNCHRONIZED_HPP

#include <phansar/common/policy/hosted_implementation_policy.hpp>
#include <phansar/common/utility/pimpl.hpp>
#include <optional>
#include <shared_mutex>

namespace phansar::common {
template <class T,
          class ImplementationPolicy = policy::hosted_implementation_policy<T>>
class synchronized {
public:
  template <bool Writable>
  class proxy {
  public:
    proxy(proxy const & _other);
    auto operator=(proxy const & _other) -> proxy &;
    proxy(proxy && _other) noexcept;
    auto operator=(proxy && _other) noexcept -> proxy &;
    virtual ~proxy();

    template <bool Writable2 = Writable, class = std::enable_if_t<Writable2>>
    auto get() -> T *;
    template <bool Writable2 = Writable, class = std::enable_if_t<Writable2>>
    auto operator*() -> T &;
    template <bool Writable2 = Writable, class = std::enable_if_t<Writable2>>
    auto operator->() -> T *;
    template <bool Writable2 = Writable, class = std::enable_if_t<! Writable2>>
    [[nodiscard]] auto get() const -> const T *;
    template <bool Writable2 = Writable, class = std::enable_if_t<! Writable2>>
    auto operator*() const -> const T &;
    template <bool Writable2 = Writable, class = std::enable_if_t<! Writable2>>
    auto operator->() const -> const T *;

  private:
    proxy(T & _obj, std::shared_mutex & _mutex);

    struct impl;
    utility::pimpl<impl> m_impl;

    friend synchronized;
  };

  template <class... Args>
  explicit constexpr synchronized(Args &&... _args);
  synchronized(synchronized const & _other);
  auto operator=(synchronized const & _other) -> synchronized &;
  synchronized(synchronized && _other) noexcept;
  auto operator=(synchronized && _other) noexcept -> synchronized &;
  virtual ~synchronized();

  auto lock() -> proxy<true>;
  auto try_lock() -> std::optional<proxy<true>>;
  auto lock_shared() -> proxy<false>;
  auto try_lock_shared() -> std::optional<proxy<false>>;

private:
  struct impl;
  utility::pimpl<impl> m_impl;
};
} // namespace phansar::common

#include <phansar/common/synchronized.inl>

#endif
