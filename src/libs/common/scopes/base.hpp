#ifndef COMMON_SCOPES_BASE_HPP
#define COMMON_SCOPES_BASE_HPP

#include <cstdint>

namespace common {
namespace scopes {
namespace internal {
template <class T> class base {
public:
    base();
    virtual ~base();

    std::uint32_t get_guards() const;

private:
    static std::uint32_t _guards;
};
} // namespace internal
} // namespace scopes
} // namespace common

#include "base.tpp"

#endif
