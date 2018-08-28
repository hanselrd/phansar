#include "enet.hpp"
#include "../core/assert.hpp"
#include "../core/log.hpp"

namespace common {
namespace scopes {
enet::enet() {
    if (_guards > 1) {
        return;
    }

    ASSERT_ALWAYS(enet_initialize() == 0);
    LOGI << "ENet initialized";
}

enet::~enet() {
    if (_guards > 1) {
        return;
    }

    enet_deinitialize();
    LOGI << "ENet shutdown";
}
} // namespace scopes
} // namespace common
