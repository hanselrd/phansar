#include "common_system.hpp"
#include "common_config.hpp"
#include "common_log.hpp"
#include "common_macros.hpp"
#include "common_memory.hpp"
#include <cstdlib>
#include <plibsys.h>
#include <string>

namespace common::system {
void init(int argc, const char * const * argv, bool enable_config) {
    if (enable_config) {
        config::init(argc, argv);

        log::init(config::get_log_file(), config::get_log_level(), config::get_binary_name());
    }

    auto vtable    = PMemVTable{};
    vtable.malloc  = &common::memory::malloc;
    vtable.realloc = &common::memory::realloc;
    vtable.free    = &common::memory::free;

    p_libsys_init_full(&vtable);
}

void shutdown() {
    p_libsys_shutdown();
}
} // namespace common::system
