#include "common_system.hpp"
#include "common_log.hpp"
#include "common_macros.hpp"
#include <string>

namespace common::system {
void init(int argc, char **argv) {
    UNUSED(argc);

    auto bin = std::string{argv[0]};

    log::init(bin.substr(bin.find_last_of('/') + 1) + ".log");
}
} // namespace common::system
