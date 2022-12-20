#include <catch2/catch.hpp>
#include <zmq.hpp>
#include <chrono>
#include <iostream>
#include <thread>

TEST_CASE("vendor::cppzmq", "[vendor][cppzmq]") {
  auto const & [major, minor, patch] = zmq::version();
  std::cout << "ZMQ Version: " << major << "." << minor << "." << patch << "\n";

  auto server_thread = std::jthread{[]() {
    auto context = zmq::context_t{2};
    auto socket  = zmq::socket_t{context, zmq::socket_type::rep};

    socket.bind("tcp://*:5555");

    bool done = false;
    do {
      auto request = zmq::message_t{};
      (void)socket.recv(request, zmq::recv_flags::none);
      std::cout << "[SERVER] Received `Hello`\n";

      std::this_thread::sleep_for(std::chrono::seconds(1));

      auto reply = zmq::message_t{5};
      std::memcpy(reply.data(), "World", 5);
      std::cout << "[SERVER] Sending `World`\n";
      socket.send(reply, zmq::send_flags::none);

      done = true;
    } while (! done);
  }};

  auto client_thread = std::jthread{[]() {
    auto context = zmq::context_t{1};
    auto socket  = zmq::socket_t{context, zmq::socket_type::req};

    socket.connect("tcp://localhost:5555");

    bool done = false;
    do {
      auto request = zmq::message_t{5};
      std::memcpy(request.data(), "Hello", 5);
      std::cout << "[CLIENT] Sending `Hello`\n";
      socket.send(request, zmq::send_flags::none);

      auto reply = zmq::message_t{};
      (void)socket.recv(reply, zmq::recv_flags::none);
      std::cout << "[CLIENT] Received `World`\n";

      done = true;
    } while (! done);
  }};
}
