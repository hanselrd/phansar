#include <phansar/common/policy/static_storage_policy.hpp>
#include <memory>
#include <new>

namespace phansar::common::policy {
template <class T, std::size_t Size, std::size_t Align>
template <class... Args>
static_storage_policy<T, Size, Align>::static_storage_policy(Args &&... _args) {
  static_assert(Size >= sizeof(T),
                "Size must be greater than or equal to sizeof(T)");
  static_assert(Size <= sizeof(T) * 1.1,
                "Size must be less than or equal to sizeof(T) with a 10% "
                "tolerance margin");
  static_assert(Align == alignof(T), "Align must be equal to alignof(T)");

  new (&m_storage) T{std::forward<Args>(_args)...};
}

template <class T, std::size_t Size, std::size_t Align>
static_storage_policy<T, Size, Align>::static_storage_policy(
    const static_storage_policy & _other)
    : m_valid{_other.m_valid} {
  if (m_valid) {
    new (&m_storage)
        T{*std::launder(reinterpret_cast<const T *>(&_other.m_storage))};
  }
}

template <class T, std::size_t Size, std::size_t Align>
auto static_storage_policy<T, Size, Align>::operator=(
    const static_storage_policy & _other)
    -> static_storage_policy<T, Size, Align> & {
  if (this != &_other) {
    if (m_valid) {
      std::destroy_at(std::launder(reinterpret_cast<T *>(&m_storage)));
    }

    if (_other.m_valid) {
      new (&m_storage)
          T{*std::launder(reinterpret_cast<const T *>(&_other.m_storage))};
    }
    m_valid = _other.m_valid;
  }

  return *this;
}

template <class T, std::size_t Size, std::size_t Align>
static_storage_policy<T, Size, Align>::static_storage_policy(
    static_storage_policy && _other) noexcept
    : m_valid{std::exchange(_other.m_valid, false)} {
  if (m_valid) {
    new (&m_storage)
        T{std::move(*std::launder(reinterpret_cast<T *>(&_other.m_storage)))};
  }
}

template <class T, std::size_t Size, std::size_t Align>
auto static_storage_policy<T, Size, Align>::operator=(
    static_storage_policy && _other) noexcept
    -> static_storage_policy<T, Size, Align> & {
  if (this != &_other) {
    if (m_valid) {
      std::destroy_at(std::launder(reinterpret_cast<T *>(&m_storage)));
    }

    if (_other.m_valid) {
      new (&m_storage)
          T{std::move(*std::launder(reinterpret_cast<T *>(&_other.m_storage)))};
    }
    m_valid = std::exchange(_other.m_valid, false);
  }

  return *this;
}

template <class T, std::size_t Size, std::size_t Align>
static_storage_policy<T, Size, Align>::~static_storage_policy() {
  if (m_valid) {
    std::destroy_at(std::launder(reinterpret_cast<T *>(&m_storage)));
  }
}

template <class T, std::size_t Size, std::size_t Align>
auto static_storage_policy<T, Size, Align>::operator*() const -> const T & {
  return *std::launder(reinterpret_cast<const T *>(&m_storage));
}

template <class T, std::size_t Size, std::size_t Align>
auto static_storage_policy<T, Size, Align>::operator*() -> T & {
  return const_cast<T &>(
      static_cast<const static_storage_policy &>(*this).operator*());
}

template <class T, std::size_t Size, std::size_t Align>
auto static_storage_policy<T, Size, Align>::operator->() const -> const T * {
  return std::launder(reinterpret_cast<const T *>(&m_storage));
}

template <class T, std::size_t Size, std::size_t Align>
auto static_storage_policy<T, Size, Align>::operator->() -> T * {
  return const_cast<T *>(
      static_cast<const static_storage_policy &>(*this).operator->());
}
} // namespace phansar::common::policy
