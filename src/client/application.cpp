#include <phansar/client/application.hpp>
#include <phansar/common/command_line.hpp>
#include <phansar/common/macros.hpp>
#include <phansar/common/networking/service.hpp>
#include <phansar/common/networking/stream.hpp>

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
        auto session = result.getOk().castAs<common::schema::Service::RootSession>();

        auto request2 = session.globalChatRequest();

        auto response2 = request2.send().wait(wait_scope);
        auto result2   = response2.getResult();

        auto chat = result2.getOk();

        if (result2.isOk()) {
            auto request3 = chat.pushPullRequest();
            request3.setStream(
                kj::heap<common::networking::stream<common::schema::Service::Chat::Packet>>(
                    std::make_shared<std::vector<
                        kj::Own<capnp::ReaderFor<common::schema::Service::Chat::Packet>>>>()));
            request3.send().wait(wait_scope);

            /* for (auto i = std::size_t{0}; i < 2; ++i) { */
            /*     auto request3 = chat.uploadRequest(); */

            /*     auto response3 = request3.send().wait(wait_scope); */

            /*     auto stream = response3.getStream(); */

            /*     for (auto j = std::size_t{0}; j < 10'000; ++j) { */
            /*         auto request4 = stream.writeRequest(); */
            /*         auto message  = request4.initPayload(); */
            /*         message.setId(static_cast<std::uint32_t>(j + 1)); */
            /*         message.setAuthor(fmt::format("Client [{}]", i)); */
            /*         message.setText("Thank you"); */

            /*         request4.send().wait(wait_scope); */
            /*     } */

            /*     stream.doneRequest().send().ignoreResult().wait(wait_scope); */
            /* } */

            /* auto request5 = chat.downloadRequest(); */
            /* request5.setStream( */
            /*     kj::heap<common::networking::stream<common::schema::Service::Message>>( */
            /*         std::make_shared<std::vector< */
            /*             kj::Own<capnp::ReaderFor<common::schema::Service::Message>>>>())); */
            /* request5.send().wait(wait_scope); */
        }

        /* auto request6 = session.banRequest(); */
        /* request6.setName("Ban me"); */
        /* request6.send().wait(wait_scope); */

        /* auto request7 = session.unbanRequest(); */
        /* request7.setName("Unban me"); */
        /* request7.send().wait(wait_scope); */

        /* session.restartRequest().send().ignoreResult().wait(wait_scope); */

        /* session.shutdownRequest().send().ignoreResult().wait(wait_scope); */

        session.logoutRequest().send().ignoreResult().wait(wait_scope);
    }
}
} // namespace phansar::client
