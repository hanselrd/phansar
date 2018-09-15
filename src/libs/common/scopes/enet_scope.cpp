#include "enet_scope.hpp"
#include "../core/assert.hpp"
#include "../core/log.hpp"

namespace common {
namespace scopes {
enet_scope::enet_scope() {
    if (get_guards() > 1) {
        return;
    }

    ASSERT_ALWAYS(enet_initialize() == 0);
    LOGI << "ENet initialized";
}

enet_scope::~enet_scope() {
    if (get_guards() > 1) {
        return;
    }

    enet_deinitialize();
    LOGI << "ENet shutdown";
}
} // namespace scopes
} // namespace common
