#include <phansar/common/application.hpp>
#include <phansar/common/cli.hpp>
#include <phansar/common/log.hpp>
#include <phansar/common/macros.hpp>
#include <phansar/common/version.hpp>

namespace phansar::common {
application::application(int _argc, const char * const * _argv) {
    cli::create(_argc, _argv);
    if (cli::instance() != nullptr) {
        log::create(cli::instance()->log_level(),
                    cli::instance()->binary_name(),
                    cli::instance()->log_file_path(),
                    10 * 1024,
                    9);
    }

    PH_LOG_INFO("██████╗ ██╗  ██╗ █████╗ ███╗   ██╗███████╗ █████╗ ██████╗ ");
    PH_LOG_INFO("██╔══██╗██║  ██║██╔══██╗████╗  ██║██╔════╝██╔══██╗██╔══██╗");
    PH_LOG_INFO("██████╔╝███████║███████║██╔██╗ ██║███████╗███████║██████╔╝");
    PH_LOG_INFO("██╔═══╝ ██╔══██║██╔══██║██║╚██╗██║╚════██║██╔══██║██╔══██╗");
    PH_LOG_INFO("██║     ██║  ██║██║  ██║██║ ╚████║███████║██║  ██║██║  ██║");
    PH_LOG_INFO("╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝");

    PH_LOG_INFO("Build: {} @ {}.{} [{}]",
                version::k_version,
                version::k_git_branch,
                version::k_git_changes,
                version::k_timestamp);
}
} // namespace phansar::common
