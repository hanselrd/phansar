#ifndef PHANSAR_COMMON_UTILITY_NONMOVABLE_HPP
#define PHANSAR_COMMON_UTILITY_NONMOVABLE_HPP

namespace phansar::common::utility {
class nonmovable {
public:
    nonmovable(nonmovable &&) = delete;
    auto operator=(nonmovable &&) -> nonmovable & = delete;

protected:
    nonmovable() = default;
};
} // namespace phansar::common::utility

#endif
