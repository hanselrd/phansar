#ifndef PHANSAR_COMMON_UTILITY_NONCOPYABLE_HPP
#define PHANSAR_COMMON_UTILITY_NONCOPYABLE_HPP

namespace phansar::common::utility {
class noncopyable {
public:
    noncopyable(const noncopyable &) = delete;
    auto operator=(const noncopyable &) -> noncopyable & = delete;
    noncopyable(noncopyable &&)                          = default;
    auto operator=(noncopyable &&) -> noncopyable & = default;
    ~noncopyable()                                  = default;

protected:
    noncopyable() = default;
};
} // namespace phansar::common::utility

#endif
