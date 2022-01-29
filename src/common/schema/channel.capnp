@0xe8081f0c94ca1229;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("phansar::common::schema");

using Chat = import "chat.capnp".Chat;
using Id = import "id.capnp".Id;
using User = import "user.capnp".User;

struct Channel {
    id @0 :Id;
    users @1 :List(User);
    chat @2 :Chat;
}
