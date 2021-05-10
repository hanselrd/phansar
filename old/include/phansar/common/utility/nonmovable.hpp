#ifndef PHANSAR_COMMON_UTILITY_NONMOVABLE_HPP
#define PHANSAR_COMMON_UTILITY_NONMOVABLE_HPP

namespace phansar::common::utility {
class nonmovable {
public:
    nonmovable(const nonmovable &) = default;
    auto operator=(const nonmovable &) -> nonmovable & = default;
    nonmovable(nonmovable &&)                          = delete;
    auto operator=(nonmovable &&) -> nonmovable & = delete;
    ~nonmovable()                                 = default;

protected:
    nonmovable() = default;
};
} // namespace phansar::common::utility

#endif
