@0xedc758d44301b726;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("phansar::common::schema");

struct Asset {
    name @0 :Text;

    union {
        data @1 :Data;
        assets @2 :List(Asset);
    }
}
