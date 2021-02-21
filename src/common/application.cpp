#include <phansar/common/application.hpp>
#include <phansar/common/command_line.hpp>
#include <phansar/common/log.hpp>
#include <phansar/common/macros.hpp>
#include <phansar/common/version.hpp>

namespace phansar::common {
application::application(int _argc, const char * const * _argv) {
    command_line::create(_argc, _argv);
    if (command_line::instance() != nullptr) {
        log::create(command_line::instance()->log_level(),
                    command_line::instance()->program_name(),
                    command_line::instance()->log_file(),
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
