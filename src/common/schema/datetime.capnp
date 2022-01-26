@0xa4da2f89a61c2f28;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("phansar::common::schema");

struct Date {
    year @0 :UInt16;
    month @1 :UInt8;
    day @2 :UInt8;
}

struct Time {
    hour @0 :UInt8;
    minute @1 :UInt8;
    second @2 :UInt8;
}

struct DateTime {
    year @0 :UInt16;
    month @1 :UInt8;
    day @2 :UInt8;
    hour @3 :UInt8;
    minute @4 :UInt8;
    second @5 :UInt8;
}
