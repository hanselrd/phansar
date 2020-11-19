#ifndef PHANSAR_COMMON_UTILITY_NONCOPYABLE_HPP
#define PHANSAR_COMMON_UTILITY_NONCOPYABLE_HPP

namespace phansar::common::utility {
class noncopyable {
public:
    noncopyable()                    = default;
    noncopyable(const noncopyable &) = delete;
    auto operator=(const noncopyable &) -> noncopyable & = delete;
    virtual ~noncopyable()                               = default;
};
} // namespace phansar::common::utility

#endif
