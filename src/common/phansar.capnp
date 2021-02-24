@0xec2afc4a6f6c4290;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("phansar::common::schema");

interface Service {
    struct Result(T, E) {
        union {
            ok @0 :T;
            err @1 :E;
        }
    }

    using Id = UInt32;

    struct Vector2 {
        x @0 :Float32 = 0;
        y @1 :Float32 = 0;
    }

    struct Vector3 {
        x @0 :Float32 = 0;
        y @1 :Float32 = 0;
        z @2 :Float32 = 0;
    }

    interface Stream(T) {
        write @0 (payload :T) -> stream;
        done @1 ();
    }

    interface Streamable(T) {
        download @0 (stream :Stream(T));
        upload @1 () -> (stream :Stream(T));
        bidi @2 (stream :Stream(T)) -> (stream :Stream(T));
    }

    interface StreamableFactory {
        create @0 [T] () -> (streamable :Streamable(T));
    }

    interface Session {
        logout @0 ();
        download @1 [T] (stream :Stream(T));
        upload @2 [T] () -> (stream :Stream(T));
        bidi @3 [T, U] (stream :Stream(T)) -> (stream :Stream(U));
    }

    interface ModeratorSession extends(Session) {
    }

    interface AdministratorSession extends(ModeratorSession) {
        restart @0 ();
    }

    interface RootSession extends(AdministratorSession) {
        shutdown @0 ();
    }

    login @0 (username :Text, password :Text) -> (result :Result(Session, Text));

    struct Message {
        id @0 :Id;
        author @1 :Text;
        text @2 :Text;
    }

    streamDown @1 (stream :Stream(Message));
    streamUp @2 () -> (stream :Stream(Message));
    streamBidi @3 (stream: Stream(Message)) -> (stream :Stream(Message));
    func @4 (id :Id, name :Text) -> (id :Id, name :Text);
}

# struct Entity {
#     enum Type {
#         player @0;
#         npc @1;
#         mob @2;
#     }

#     id @0 :Id;
#     type @1 :Type;
# }

# struct Packet {
#     entity @0 :Entity;

#     union {
#         heartbeat @1 :Void;

#         position :group {
#             absolute @2 :Vector3;
#             delta @3 :Vector3;
#         }
#     }
# }
