@0xc816276ae4dc94d7;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("phansar::common::schema");

struct Vector1 {
    x @0 :Float32 = 0;
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

struct Vector4 {
    x @0 :Float32 = 0;
    y @1 :Float32 = 0;
    z @2 :Float32 = 0;
    w @3 :Float32 = 0;
}
