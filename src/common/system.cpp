#include <phansar/common/config.hpp>
#include <phansar/common/log.hpp>
#include <phansar/common/macros.hpp>
#include <phansar/common/memory.hpp>
#include <phansar/common/system.hpp>

#include <phansar/vendor/plibsys.hpp>

#include <cstdlib>
#include <string>

namespace phansar::common::system {
void init(int argc, const char * const * argv, bool enable_config) {
    if (enable_config) {
        config::init(argc, argv);

        log::init(config::get_log_file(), config::get_log_level(), config::get_binary_name());
    }

    auto vtable    = PMemVTable{};
    vtable.malloc  = &memory::malloc;
    vtable.realloc = &memory::realloc;
    vtable.free    = &memory::free;

    p_libsys_init_full(&vtable);
}

void shutdown() {
    p_libsys_shutdown();
}
} // namespace phansar::common::system
