#include "common_system.hpp"
#include "common_log.hpp"
#include "common_macros.hpp"
#include <cstdlib>
#include <plibsys.h>
#include <string>

namespace common::system {
void init(int argc, char **argv) {
    auto bin = std::string{argv[0]};

    log::init(bin.substr(bin.find_last_of('/') + 1) + ".log");

    // postponed until after we initialize logger
    UNUSED_ARG(argc);

    auto vtable = PMemVTable{};
    vtable.malloc = [](psize nbytes) {
        auto ptr = std::malloc(nbytes);
        LOGD("Allocated {} bytes at {}", nbytes, ptr);
        return ptr;
    };
    vtable.realloc = [](ppointer mem, psize nbytes) {
        auto ptr = std::realloc(mem, nbytes);
        LOGD("Reallocated {} bytes at {} from {}", nbytes, ptr, mem);
        return ptr;
    };
    vtable.free = [](ppointer mem) {
        std::free(mem);
        LOGD("Freed {}", mem);
    };

    p_libsys_init_full(&vtable);
}

void shutdown() {
    p_libsys_shutdown();
}
} // namespace common::system
