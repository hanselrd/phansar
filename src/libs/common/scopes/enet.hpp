#ifndef COMMON_SCOPES_ENET_HPP
#define COMMON_SCOPES_ENET_HPP

#include "base.hpp"
#include <enet/enet.h>

namespace common {
namespace scopes {
class enet : private internal::base<enet> {
public:
    enet();
    ~enet();
};
} // namespace scopes
} // namespace common

#endif
