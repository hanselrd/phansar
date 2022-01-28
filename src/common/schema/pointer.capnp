@0x9f10088d16c3ed20;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("phansar::common::schema");

struct PVoid {
    value @0 :Void;
}

struct PBool {
    value @0 :Bool;
}

struct PInt8 {
    value @0 :Int8;
}

struct PInt16 {
    value @0 :Int16;
}

struct PInt32 {
    value @0 :Int32;
}

struct PInt64 {
    value @0 :Int64;
}

struct PUInt8 {
    value @0 :UInt8;
}

struct PUInt16 {
    value @0 :UInt16;
}

struct PUInt32 {
    value @0 :UInt32;
}

struct PUInt64 {
    value @0 :UInt64;
}

struct PFloat32 {
    value @0 :Float32;
}

struct PFloat64 {
    value @0 :Float64;
}
