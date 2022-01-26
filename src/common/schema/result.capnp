
@0xf064931f354b9d81;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("phansar::common::schema");

struct Result(T, E) {
    union {
        ok @0 :T;
        err @1 :E;
    }
}
