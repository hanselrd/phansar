#ifndef COMMON_SCOPES_PLIBSYS_HPP
#define COMMON_SCOPES_PLIBSYS_HPP

#include "base.hpp"
#include <plibsys.h>

namespace common {
namespace scopes {
class plibsys : private internal::base<plibsys> {
public:
    explicit plibsys(const PMemVTable *vtable = nullptr);
    ~plibsys();
};
} // namespace scopes
} // namespace common

#endif
