@0xa5c935413835aa78;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("phansar::common::schema");

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
