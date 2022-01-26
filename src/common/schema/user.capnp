@0xc74666b2d36a45d7;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("phansar::common::schema");

using DT = import "datetime.capnp";
using Id = import "id.capnp".Id;

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

    banned @3 :Bool;
    hidden @4 :Bool;

    metadata @5 :Metadata;

    struct Metadata {
        creationDateTime @0 :DT.DateTime;
        lastLoginDateTime @1 :DT.DateTime;
    }
}
