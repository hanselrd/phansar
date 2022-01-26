@0xa5c935413835aa78;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("phansar::common::schema");

using Id = UInt32;
using Ref = List;

struct Result(T, E) {
    union {
        ok @0 :T;
        err @1 :E;
    }
}

struct Person {
    name @0 :Text;
    birthdate @3 :Date;

    email @1 :Text;
    phones @2 :List(PhoneNumber);

    struct PhoneNumber {
        number @0 :Text;
        type @1 :Type;

        enum Type {
            mobile @0;
            home @1;
            work @2;
        }
    }
}

struct Date {
    year @0 :UInt16;
    month @1 :UInt8;
    day @2 :UInt8;
}

struct Vector2 {
    x @0 :Float32 = 0;
    y @1 :Float32 = 0;
}

struct Vector3 {
    x @0 :Float32 = 0;
    y @1 :Float32 = 0;
    z @2 :Float32 = 0;
}

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
