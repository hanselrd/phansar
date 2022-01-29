@0xf5893184dbbb8117;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("phansar::common::schema");

using Id = import "id.capnp".Id;
using Timestamp = import "datetime.capnp".Timestamp;
using User = import "user.capnp".User;

struct Chat {
    id @0 :Id;

    messages @1 :List(Message);

    struct Message {
        id @0 :Id;
        user @1 :User; # maybe just store userId?
        text @2 :Text;
    }
}
