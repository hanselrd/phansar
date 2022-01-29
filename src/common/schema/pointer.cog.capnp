@0x9f10088d16c3ed20;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("phansar::common::schema");

#[[[cog
#   import cog
#   def pointer(name: str) -> None:
#       cog.out(f"""
#           struct {name}T {{
#               value @0 :{name};
#           }}
#       """, dedent=True, trimblanklines=True)
#   pointer("Void")
#   pointer("Bool")
#   for bits in [8, 16, 32, 64]:
#       pointer(f"Int{bits}")
#   for bits in [8, 16, 32, 64]:
#       pointer(f"UInt{bits}")
#   for bits in [32, 64]:
#       pointer(f"Float{bits}")
#]]]
struct VoidT {
    value @0 :Void;
}
struct BoolT {
    value @0 :Bool;
}
struct Int8T {
    value @0 :Int8;
}
struct Int16T {
    value @0 :Int16;
}
struct Int32T {
    value @0 :Int32;
}
struct Int64T {
    value @0 :Int64;
}
struct UInt8T {
    value @0 :UInt8;
}
struct UInt16T {
    value @0 :UInt16;
}
struct UInt32T {
    value @0 :UInt32;
}
struct UInt64T {
    value @0 :UInt64;
}
struct Float32T {
    value @0 :Float32;
}
struct Float64T {
    value @0 :Float64;
}
#[[[end]]]
