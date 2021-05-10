#include <phansar/common/application.hpp>
#include <phansar/common/command_line.hpp>
#include <phansar/common/log.hpp>
#include <phansar/common/macros.hpp>
#include <phansar/common/version.hpp>
#include <phansar/vendor/taskflow.hpp>

namespace phansar::common {
struct application::impl {
    std::unique_ptr<tf::Executor> executor;
};

application::application(int _argc, const char * const * _argv) {
    command_line::create(_argc, _argv);
    log::create(command_line::instance()->log_level(),
                command_line::instance()->program_name(),
                command_line::instance()->log_file(),
                10 * 1024,
                9);

    if (command_line::instance()->jobs() > 0) {
        m_impl->executor = std::make_unique<tf::Executor>(command_line::instance()->jobs());
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

application::~application() = default;
} // namespace phansar::common
