@0xe480a9eb4737c6c0;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("phansar::common::schema");

using Id = import "id.capnp".Id;
using Vector3 = import "vector.capnp".Vector3;

struct Packet {
    id @0 :Id;

    union {
        noop @1 :Void;
        heartbeat @2 :Void;

        raw :group {
            name @3 :Text;
            data @4 :Data;
        }

        position :group {
            dt @5 :Vector3;
        }
    }
}
