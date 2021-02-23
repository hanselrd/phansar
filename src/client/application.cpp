#include <phansar.capnp.h>
#include <phansar/client/application.hpp>
#include <phansar/common/command_line.hpp>
#include <phansar/common/networking/stream.hpp>

namespace phansar::client {
application::application(int _argc, const char * const * _argv)
    : common::application{_argc, _argv}, m_client{common::command_line::instance()->host(),
                                                  common::command_line::instance()->port()} {}

void application::run() {
    auto & wait_scope = m_client.getWaitScope();

    auto cap = m_client.getMain<common::schema::Service>();

    {
        auto request = cap.funcRequest();
        request.setId(123);
        request.setName("Hello");
        auto promise = request.send();

        auto response = promise.wait(wait_scope);

        PH_LOG_INFO("[server] {{func}}: {}", response.toString().flatten().cStr());
    }

    {
        auto request = cap.streamDownRequest();
        request.setStream(kj::heap<common::networking::stream<common::schema::Service::Message>>());
        auto promise = request.send();

        auto response = promise.wait(wait_scope);

        PH_LOG_INFO("[server] {{streamDown}}: {}", response.toString().flatten().cStr());
    }

    {
        auto request = cap.streamUpRequest();

        auto promise = request.send();

        auto response = promise.wait(wait_scope);

        for (auto i = std::size_t{0}; i < 10'000; ++i) {
            auto req     = response.getStream().writeRequest();
            auto message = req.initPayload();
            message.setId(static_cast<std::uint32_t>(i + 1));
            message.setAuthor("Client");
            message.setText("Thank you");
            req.send().wait(wait_scope);
        }

        {
            auto req = response.getStream().doneRequest();
            req.send().ignoreResult().wait(wait_scope);
        }

        PH_LOG_INFO("[server] {{streamUp}}: {}", response.toString().flatten().cStr());
    }
}
} // namespace phansar::client
