@0xd4e73dea4d311fd6;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("phansar::common::schema");

using Channel = import "channel.capnp".Channel;
using Id = import "id.capnp".Id;

struct World {
    id @0 :Id;
    name @1 :Text;
    announcements @2 :List(Text);
    channels @3 :List(Channel);
}
