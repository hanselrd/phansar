#include <phansar/common/application.hpp>
#include <phansar/common/macros.hpp>
#include <phansar/common/version.hpp>

namespace phansar::common {
application::application(int _argc, const char * const * _argv) {
    PH_UNUSED(_argc);
    PH_UNUSED(_argv);

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
