#include <phansar/common/command_line.hpp>
#include <phansar/common/macros.hpp>
#include <phansar/common/networking/service.hpp>
#include <phansar/server/application.hpp>

namespace phansar::server {
application::application(int _argc, const char * const * _argv)
    : common::application{_argc, _argv}, m_server{kj::heap<common::networking::service>(),
                                                  common::command_line::instance()->host(),
                                                  common::command_line::instance()->port()} {}

void application::run() {
    auto & wait_scope = m_server.getWaitScope();

    auto port = m_server.getPort().wait(wait_scope);
    if (port == 0) {
        PH_LOG_INFO("Listening on Unix socket ...");
    } else {
        PH_LOG_INFO("Listening on {}:{} ...", common::command_line::instance()->host(), port);
    }

    kj::NEVER_DONE.wait(wait_scope);
}
} // namespace phansar::server
