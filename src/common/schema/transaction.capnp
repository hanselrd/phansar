@0x91e2f43cb3eb347a;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("phansar::common::schema");

using Result = import "result.capnp".Result;

struct Transaction(Request, Response) {
    union {
        request @0 :Request;
        response @1 :Result(Response, Text);
    }
}
