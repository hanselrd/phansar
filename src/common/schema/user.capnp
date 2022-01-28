@0xc74666b2d36a45d7;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("phansar::common::schema");

using Id = import "id.capnp".Id;
using Timestamp = import "datetime.capnp".Timestamp;

struct User {
    id @0 :Id;
    name @1 :Text;

    roles @2 :List(Role);

    enum Role {
        donor @0;
        intern @1;
        moderator @2;
        administrator @3;
        root @4;
    }

    flags @3 :List(Flag);

    enum Flag {
        banned @0;
        hidden @1;
        blocked @2;
    }

    metadata @4 :Metadata;

    struct Metadata {
        creationTimestamp @0 :Timestamp;
        lastLoginTimestamp @1 :Timestamp;
        publicKey @2 :Text;
    }
}
