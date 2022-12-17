#include <catch2/catch.hpp>
#include <zmq.hpp>
#include <chrono>
#include <iostream>
#include <thread>

TEST_CASE("vendor::cppzmq", "[vendor][cppzmq]") {
#if 0
  auto context = zmq::context_t{2};
  auto socket  = zmq::socket_t{context, zmq::socket_type::rep};

  socket.bind("tcp://*:5555");

  /* while (true) { */
  auto request = zmq::message_t{};

  (void)socket.recv(request, zmq::recv_flags::none);
  std::cout << "Received `hello`\n";

  std::this_thread::sleep_for(std::chrono::seconds(1));

  auto reply = zmq::message_t{5};
  std::memcpy(reply.data(), "World", 5);
  socket.send(reply, zmq::send_flags::none);
  /* } */
#endif
}
