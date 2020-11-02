#include <phansar/common/cli.hpp>
#include <phansar/common/log.hpp>
#include <phansar/common/macros.hpp>
#include <phansar/common/memory.hpp>
#include <phansar/common/system.hpp>

namespace phansar::common::system {
void init(int _argc, const char * const * _argv, bool _enable_config) {
    if (_enable_config) {
        cli::create(_argc, _argv);

        if (cli::instance() != nullptr) {
            log::create(cli::instance()->log_level(),
                        cli::instance()->binary_name(),
                        cli::instance()->log_file_path(),
                        5 * 1024 * 1024,
                        3);
        }
    }
}

void shutdown() {}
} // namespace phansar::common::system
