@0xe480a9eb4737c6c0;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("phansar::common::schema");

using Channel = import "channel.capnp".Channel;
using Id = import "id.capnp".Id;
using Ptr = import "pointer.capnp";
using Publish = import "publish.capnp".Publish;
using TC = import "transaction_chain.capnp";
using Timestamp = import "datetime.capnp".Timestamp;
using TimestampDiff = import "datetime.capnp".TimestampDiff;
using Transaction = import "transaction.capnp".Transaction;
using User = import "user.capnp".User;
using Vector3 = import "vector.capnp".Vector3;
using World = import "world.capnp".World;

struct Packet {
    header @0 :Header;

    struct Header {
        id @0 :Id;

        sendTimestamp @1 :Timestamp;
        receiveTimestamp @2 :Timestamp;
        latency @3 :TimestampDiff;
    }

    union {
        data :group {
            name @1 :Text;
            value @2 :Data;
        }

        auth :union {
            logIn @3 :TC.TransactionChain3(
                Transaction(Detail.Auth.LogIn.Transaction0.Request, Detail.Auth.LogIn.Transaction0.Response),
                Transaction(Detail.Auth.LogIn.Transaction1.Request, Detail.Auth.LogIn.Transaction1.Response),
                Transaction(Detail.Auth.LogIn.Transaction2.Request, Detail.Auth.LogIn.Transaction2.Response));

            logOut @4 :Transaction(Ptr.PVoid, Ptr.PVoid);
        }

        user :union {
            placeholder @5 :Void;

            updatePosition @6 :Publish(Vector3);
        }

        refresh :union {
            world @7 :Transaction(Ptr.PVoid, World);
            channel @8 :Transaction(Ptr.PVoid, Channel);
            user @9 :Transaction(Ptr.PVoid, User);
        }
    }

    struct Detail {
        struct Auth {
            struct LogIn {
                struct Transaction0 {
                    struct Request {
                        userName @0 :Text;
                        password @1 :Text;
                    }

                    struct Response {
                        worlds @0 :List(World);
                    }
                }

                struct Transaction1 {
                    struct Request {
                        worldId @0 :Id;
                    }

                    struct Response {
                        channels @0 :List(Channel);
                    }
                }

                struct Transaction2 {
                    struct Request {
                        channelId @0 :Id;
                    }

                    struct Response {
                        world @0 :World;
                        channel @1 :Channel;
                        user @2 :User;
                    }
                }
            }
        }
    }
}
