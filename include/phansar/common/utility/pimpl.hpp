#ifndef PHANSAR_COMMON_UTILITY_PIMPL_HPP
#define PHANSAR_COMMON_UTILITY_PIMPL_HPP

#include <memory>

#ifdef __has_include
    #if __has_include(<experimental/propagate_const>)
        #include <experimental/propagate_const>
    #endif
#endif

namespace phansar::common::utility {
template <class T>
class pimpl {
public:
    template <class... Args>
    explicit pimpl(Args &&... _args);
    pimpl(const pimpl & _other);
    auto operator            =(const pimpl & _other) -> pimpl &;
    pimpl(pimpl &&) noexcept = default;
    auto operator=(pimpl &&) noexcept -> pimpl & = default;
    ~pimpl()                                     = default;

    auto operator*() const -> const T &;
    auto operator*() -> T &;
    auto operator->() const -> const T *;
    auto operator->() -> T *;

private:
#ifdef __has_include
    #if __has_include(<experimental/propagate_const>)
    std::experimental::propagate_const<std::unique_ptr<T>>
    #else
    std::unique_ptr<T>
    #endif
#endif
        m_instance;
};
} // namespace phansar::common::utility

#include <phansar/common/utility/pimpl.inl>

#endif
