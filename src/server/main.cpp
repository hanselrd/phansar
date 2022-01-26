#include <phansar/common/macro.hpp>
#include <phansar/common/network/socket.hpp>
#include <phansar/common/service/executor_service.hpp>
#include <phansar/common/service/logger_service.hpp>
#include <phansar/common/service_container.hpp>
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <enet/enet.h>
#include <iostream>
#include <phansar.capnp.h>

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
    packet.setId(0xFF);
    auto position = packet.initPosition();
    auto dt       = position.initDt();
    dt.setX(12.0F);
    dt.setY(23.0F);
    dt.setZ(34.0F);
    // auto raw = packet.initRaw();
    // raw.setName("payload");
    // auto data = raw.initData(100);
    // std::memset(data.begin(), static_cast<int>(data.size()), 0x7e);

    {
        auto stream = kj::VectorOutputStream{};
        capnp::writeMessage(stream, message);
        const auto u = stream.getArray();
        PH_LOG_DEBUG("u.encoded[{}]= {:#04x}", u.size(), fmt::join(u, ", "));

        auto array   = kj::ArrayInputStream{kj::arrayPtr(u.begin(), u.size())};
        auto reader  = capnp::InputStreamMessageReader{array};
        auto decoded = reader.getRoot<phansar::common::schema::Packet>();
        PH_LOG_DEBUG("id= {}", decoded.getId());
        switch (decoded.which()) {
        case phansar::common::schema::Packet::NOOP:
        case phansar::common::schema::Packet::HEARTBEAT:
            break;
        case phansar::common::schema::Packet::POSITION: {
            auto position = decoded.getPosition();
            auto dt       = position.getDt();
            PH_LOG_DEBUG("x= {}", dt.getX());
            PH_LOG_DEBUG("y= {}", dt.getY());
            PH_LOG_DEBUG("z= {}", dt.getZ());
        } break;
        case phansar::common::schema::Packet::RAW: {
            auto raw  = decoded.getRaw();
            auto data = raw.getData();
            PH_LOG_DEBUG("raw.name= {}", raw.getName().cStr());
            PH_LOG_DEBUG("raw.data.size= {}", data.size());
        } break;
        }
    }

    {
        auto stream = kj::VectorOutputStream{};
        capnp::writePackedMessage(stream, message);
        const auto p = stream.getArray();
        PH_LOG_DEBUG("p.encoded[{}]= {:#04x}", p.size(), fmt::join(p, ", "));

        auto array   = kj::ArrayInputStream{kj::arrayPtr(p.begin(), p.size())};
        auto reader  = capnp::PackedMessageReader{array};
        auto decoded = reader.getRoot<phansar::common::schema::Packet>();
        PH_LOG_DEBUG("id= {}", decoded.getId());
        switch (decoded.which()) {
        case phansar::common::schema::Packet::NOOP:
        case phansar::common::schema::Packet::HEARTBEAT:
            break;
        case phansar::common::schema::Packet::POSITION: {
            auto position = decoded.getPosition();
            auto dt       = position.getDt();
            PH_LOG_DEBUG("x= {}", dt.getX());
            PH_LOG_DEBUG("y= {}", dt.getY());
            PH_LOG_DEBUG("z= {}", dt.getZ());
        } break;
        case phansar::common::schema::Packet::RAW: {
            auto raw  = decoded.getRaw();
            auto data = raw.getData();
            PH_LOG_DEBUG("raw.name= {}", raw.getName().cStr());
            PH_LOG_DEBUG("raw.data.size= {}", data.size());
        } break;
        }
    }

    {
        int rc = enet_initialize();
        PH_ASSERT(rc == 0);

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
                socket.poll(10000);
                const auto [client_id, data] =
                    *socket.receive(phansar::common::network::socket::channel::reliable);
                PH_LOG_DEBUG("received {} byte(s) from server", data.size());
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
