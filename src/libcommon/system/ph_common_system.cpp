#include "ph_common_system.hpp"
#include "ph_common_log.hpp"
#include "ph_common_macros.hpp"
#include <string>

namespace ph::common::system {
void init(int argc, char **argv) {
    PH_UNUSED(argc);

    auto bin = std::string{argv[0]};

    log::init(bin.substr(bin.find_last_of('/') + 1) + ".log");
}
} // namespace ph::common::system
