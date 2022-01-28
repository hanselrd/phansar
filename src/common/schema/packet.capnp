@0xe480a9eb4737c6c0;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("phansar::common::schema");

using Channel = import "channel.capnp".Channel;
using Id = import "id.capnp".Id;
using Publish = import "publish.capnp".Publish;
using Ref = List;
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
                Transaction(Detail.Auth.LogIn.Request0, Detail.Auth.LogIn.Response0),
                Transaction(Detail.Auth.LogIn.Request1, Detail.Auth.LogIn.Response1),
                Transaction(Detail.Auth.LogIn.Request2, Detail.Auth.LogIn.Response2));

            logOut @4 :Transaction(Ref(Void), Ref(Void));
        }

        user :union {
            placeholder @5 :Void;

            updatePosition @6 :Publish(Vector3);
        }
    }

    struct Detail {
        struct Auth {
            struct LogIn {
                struct Request0 {
                    userName @0 :Text;
                    password @1 :Text;
                }

                struct Response0 {
                    worlds @0 :List(World);
                }

                struct Request1 {
                    worldId @0 :Id;
                }

                struct Response1 {
                    channels @0 :List(Channel);
                }

                struct Request2 {
                    channelId @0 :Id;
                }

                struct Response2 {
                    world @0 :World;
                    channel @1 :Channel;
                    user @2 :User;
                }
            }
        }
    }
}
