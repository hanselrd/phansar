#ifndef PHANSAR_COMMON_UTILITY_NONMOVABLE_HPP
#define PHANSAR_COMMON_UTILITY_NONMOVABLE_HPP

namespace phansar::common::utility {
class nonmovable {
public:
    nonmovable()              = default;
    nonmovable(nonmovable &&) = delete;
    auto operator=(nonmovable &&) -> nonmovable & = delete;
    virtual ~nonmovable()                         = default;
};
} // namespace phansar::common::utility

#endif
