@0xa4da2f89a61c2f28;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("phansar::common::schema");

struct Date {
    year @0 :UInt16 = 1970;
    month @1 :UInt8 = 1;
    day @2 :UInt8 = 1;
}

struct Time {
    hour @0 :UInt8 = 0;
    minute @1 :UInt8 = 0;
    second @2 :UInt8 = 0;
}

struct DateTime {
    date @0 :Date = (year = 1970, month = 1, day = 1);
    time @1 :Time = (hour = 0, minute = 0, second = 0);
}

using Timestamp = UInt64;
using TimestampDiff = UInt64;
