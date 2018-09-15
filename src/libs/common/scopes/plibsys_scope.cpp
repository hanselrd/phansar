#include "plibsys_scope.hpp"
#include "../core/log.hpp"

namespace common {
namespace scopes {
plibsys_scope::plibsys_scope(const PMemVTable *vtable) {
    if (get_guards() > 1) {
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

plibsys_scope::~plibsys_scope() {
    if (get_guards() > 1) {
        return;
    }

    p_libsys_shutdown();
    LOGI << "plibsys shutdown";
}
} // namespace scopes
} // namespace common
