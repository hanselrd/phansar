#include <phansar/common/macro.hpp>
#include <phansar/common/network/socket.hpp>
#include <phansar/common/schema/asset.capnp.h>
#include <phansar/common/schema/packet.capnp.h>
#include <phansar/common/service/executor_service.hpp>
#include <phansar/common/service/logger_service.hpp>
#include <phansar/common/service_container.hpp>
#include <capnp/compat/json.h>
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <enet/enet.h>
#include <chrono>
#include <iostream>

auto main(int _argc, char * _argv[]) -> int {
    PH_UNUSED(_argc);
    PH_UNUSED(_argv);

    phansar::common::g_service_container.emplace<phansar::common::service::logger_service>(
        "server",
        "logs/server.log",
        static_cast<std::size_t>(1024 * 1024 * 5),
        3);

    phansar::common::g_service_container.emplace<phansar::common::service::executor_service>();

    auto & executor =
        phansar::common::g_service_container.service<phansar::common::service::executor_service>();

    auto message = capnp::MallocMessageBuilder{};

    auto packet = message.initRoot<phansar::common::schema::Packet>();
    auto header = packet.initHeader();
    header.setId(0xFF);
    // auto user = header.initUser();
    // user.setId(0x11);
    // user.setName("client");
    // auto roles = user.initRoles(2);
    // roles.set(0, phansar::common::schema::User::Role::DONOR);
    // roles.set(1, phansar::common::schema::User::Role::INTERN);
    // auto flags = user.initFlags(1);
    // flags.set(0, phansar::common::schema::User::Flag::HIDDEN);
    header.setSendTimestamp(std::chrono::duration_cast<std::chrono::nanoseconds>(
                                std::chrono::system_clock::now().time_since_epoch())
                                .count());
    auto auth    = packet.initAuth();
    auto logIn   = auth.initLogIn();
    auto transaction0 = logIn.initTransaction0();
    auto request = transaction0.initRequest();
    request.setUserName("bob");
    request.setPassword("password");
    // auto position = packet.initPosition();
    // auto dt       = position.initDt();
    // dt.setX(12.0F);
    // dt.setY(23.0F);
    // dt.setZ(34.0F);
    // auto data = packet.initData();
    // data.setName("public_key");
    // auto value = data.initValue(50);
    // std::memset(value.begin(), 0x05, static_cast<int>(value.size()));

    {
        auto stream = kj::VectorOutputStream{};
        capnp::writeMessage(stream, message);
        const auto u = stream.getArray();
        PH_LOG_DEBUG("u.encoded[{}]= {:#04x}", u.size(), fmt::join(u, ", "));

        auto array   = kj::ArrayInputStream{kj::arrayPtr(u.begin(), u.size())};
        auto reader  = capnp::InputStreamMessageReader{array};
        auto builder = capnp::MallocMessageBuilder{};
        builder.setRoot(reader.getRoot<phansar::common::schema::Packet>());
        auto decoded = builder.getRoot<phansar::common::schema::Packet>();
        auto header  = decoded.getHeader();
        header.setReceiveTimestamp(std::chrono::duration_cast<std::chrono::nanoseconds>(
                                       std::chrono::system_clock::now().time_since_epoch())
                                       .count());
        header.setLatency(header.getReceiveTimestamp() - header.getSendTimestamp());
        PH_LOG_DEBUG("packet= {}", decoded.toString().flatten().cStr());
        auto json        = capnp::JsonCodec{};
        auto packet_json = json.encode(decoded);
        PH_LOG_DEBUG("packet[json]= {}", packet_json.cStr());
    }

    {
        auto stream = kj::VectorOutputStream{};
        capnp::writePackedMessage(stream, message);
        const auto p = stream.getArray();
        PH_LOG_DEBUG("p.encoded[{}]= {:#04x}", p.size(), fmt::join(p, ", "));

        auto array   = kj::ArrayInputStream{kj::arrayPtr(p.begin(), p.size())};
        auto reader  = capnp::PackedMessageReader{array};
        auto builder = capnp::MallocMessageBuilder{};
        builder.setRoot(reader.getRoot<phansar::common::schema::Packet>());
        auto decoded = builder.getRoot<phansar::common::schema::Packet>();
        auto header  = decoded.getHeader();
        header.setReceiveTimestamp(std::chrono::duration_cast<std::chrono::nanoseconds>(
                                       std::chrono::system_clock::now().time_since_epoch())
                                       .count());
        header.setLatency(header.getReceiveTimestamp() - header.getSendTimestamp());
        PH_LOG_DEBUG("packet= {}", decoded.toString().flatten().cStr());
        auto json        = capnp::JsonCodec{};
        auto packet_json = json.encode(decoded);
        PH_LOG_DEBUG("packet[json]= {}", packet_json.cStr());
    }

    return 0;

    {
        int rc = enet_initialize();
        PH_ASSERT_ALWAYS(rc == 0);

        auto taskflow = tf::Taskflow{"enet"};
        taskflow.emplace(
            []() {
                auto socket = phansar::common::network::socket{
                    phansar::common::network::socket::type::server};
                socket.open(7000);
                socket.poll(10000);
                auto str = std::string{"hi"};
                socket.broadcast(phansar::common::network::socket::channel::reliable,
                                 std::launder(reinterpret_cast<std::uint8_t *>(str.data())),
                                 str.size() + 1);
                socket.close();
            },
            []() {
                auto socket = phansar::common::network::socket{
                    phansar::common::network::socket::type::client};
                socket.open("localhost", 7000);
                socket.poll(5000);
                socket.close();
            },
            []() {
                auto socket = phansar::common::network::socket{
                    phansar::common::network::socket::type::client};
                socket.open("localhost", 7000);
                socket.poll(5000);
                // const auto [client_id, data] =
                //     *socket.receive(phansar::common::network::socket::channel::reliable);
                // PH_LOG_DEBUG("received {} byte(s) from server", data.size());
                socket.close();
            },
            []() {
                auto socket = phansar::common::network::socket{
                    phansar::common::network::socket::type::client};
                socket.open("localhost", 7000);
                socket.poll(5000);
                socket.close();
            });

        executor.run(taskflow).wait();
        executor.wait_for_all();
        enet_deinitialize();
    }

    return 0;
}
