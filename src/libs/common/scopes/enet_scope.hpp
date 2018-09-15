#ifndef COMMON_SCOPES_ENET_HPP
#define COMMON_SCOPES_ENET_HPP

#include "base.hpp"
#include <enet/enet.h>

namespace common {
namespace scopes {
class enet_scope : public internal::base<enet_scope> {
public:
    enet_scope();
    ~enet_scope();
};
} // namespace scopes
} // namespace common

#endif
