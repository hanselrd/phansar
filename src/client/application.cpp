#include <phansar/client/application.hpp>
#include <phansar/common/command_line.hpp>
#include <phansar/common/macros.hpp>
#include <phansar/common/networking/service.hpp>

namespace phansar::client {
application::application(int _argc, const char * const * _argv)
    : common::application{_argc, _argv}, m_client{common::command_line::instance()->host(),
                                                  common::command_line::instance()->port()} {}

void application::run() {
    auto & wait_scope = m_client.getWaitScope();

    auto cap = m_client.getMain<common::schema::Service>();

    auto request = cap.loginRequest();
    request.setUsername("bob");
    request.setPassword("password");

    auto response = request.send().wait(wait_scope);
    auto result   = response.getResult();

    PH_LOG_INFO("[server] {{login}}: {}", response.toString().flatten().cStr());

    if (result.isOk()) {
        auto session = result.getOk();

        auto request2 = session.uploadRequest<common::schema::Service::Message>();

        auto response2 = request2.send().wait(wait_scope);

        auto stream = response2.getStream();

        for (auto i = std::size_t{0}; i < 10'000; ++i) {
            auto request3 = stream.writeRequest();
            auto message  = request3.initPayload();
            message.setId(static_cast<std::uint32_t>(i + 1));
            message.setAuthor("Client");
            message.setText("Thank you");

            request3.send().wait(wait_scope);
        }

        stream.doneRequest().send().ignoreResult().wait(wait_scope);

        session.logoutRequest().send().ignoreResult().wait(wait_scope);
    }
}
} // namespace phansar::client
