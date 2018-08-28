#include "plibsys.hpp"
#include "../core/log.hpp"

namespace common {
namespace scopes {
plibsys::plibsys(const PMemVTable *vtable) {
    if (_guards > 1) {
        return;
    }

    if (vtable) {
        p_libsys_init_full(vtable);
        LOGI << "plibsys initialized (full)";
    } else {
        p_libsys_init();
        LOGI << "plibsys initialized";
    }
}

plibsys::~plibsys() {
    if (_guards > 1) {
        return;
    }

    p_libsys_shutdown();
    LOGI << "plibsys shutdown";
}
} // namespace scopes
} // namespace common
