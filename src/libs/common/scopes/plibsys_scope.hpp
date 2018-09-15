#ifndef COMMON_SCOPES_PLIBSYS_HPP
#define COMMON_SCOPES_PLIBSYS_HPP

#include "base.hpp"
#include <plibsys.h>

namespace common {
namespace scopes {
class plibsys_scope : public internal::base<plibsys_scope> {
public:
    explicit plibsys_scope(const PMemVTable *vtable = nullptr);
    ~plibsys_scope();
};
} // namespace scopes
} // namespace common

#endif
