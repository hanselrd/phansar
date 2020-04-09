#include "common_system.hpp"
#include "common_log.hpp"
#include "common_macros.hpp"
#include "common_memory.hpp"
#include <cstdlib>
#include <plibsys.h>
#include <string>

namespace common::system {
void init(int argc, char **argv) {
    auto bin = std::string{argv[0]};

    log::init(bin.substr(bin.find_last_of('/') + 1) + ".log");

    // postponed until after we initialize logger
    UNUSED_ARG(argc);

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
