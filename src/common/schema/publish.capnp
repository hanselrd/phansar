@0xdc43675ba95a5606;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("phansar::common::schema");

struct Publish(Event) {
    event @0 :Event;
}
