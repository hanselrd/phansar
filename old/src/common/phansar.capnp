@0xaa267f9513881475;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("phansar::common::schema");

interface Service {
    using Id = UInt32;
    using Ref = List;

    struct Result(T, E) {
        union {
            ok @0 :T;
            err @1 :E;
        }
    }

    # struct Vector2 {
    #     x @0 :Float32 = 0;
    #     y @1 :Float32 = 0;
    # }

    # struct Vector3 {
    #     x @0 :Float32 = 0;
    #     y @1 :Float32 = 0;
    #     z @2 :Float32 = 0;
    # }

    struct Message {
        id @0 :Id;
        author @1 :Text;
        text @2 :Text;
    }

    # struct Entity {
    #     enum Type {
    #         player @0;
    #         npc @1;
    #         mob @2;
    #     }

    #     struct Component {
    #         union {
    #             position @0 :Vector3;

    #             health :group {
    #                 value @1 :UInt32;
    #                 maximum @2 :UInt32;
    #             }
    #         }
    #     }

    #     id @0 :Id;
    #     type @1 :Type;
    #     components @2 :List(Component);
    # }

    # struct Map {
    #     enum Type {
    #         public @0;
    #         protected @1;
    #         private @2;
    #     }

    #     id @0 :Id;
    #     type @1 :Type;
    #     npcs @2 :List(Entity);
    #     mobs @3 :List(Entity);
    # }

    interface Stream(T) {
        write @0 (payload :T) -> stream;
        done @1 ();
    }

    interface ClientStreamable(T) {
        push @0 () -> (stream :Stream(T));
    }

    interface ServerStreamable(T) {
        pull @0 (stream :Stream(T));
    }

    interface BidiStreamable(T) {
        pushPull @0 (stream :Stream(T)) -> (stream :Stream(T));
    }

    interface Chat extends (BidiStreamable(Packet)) {
        struct Packet {
            union {
                noop @0 :Void;
                message @1 :Message;
            }
        }
    }

    interface Session {
        globalChat @0 () -> (result :Result(Chat, Text));
        logout @1 ();
    }

    interface ModeratorSession extends (Session) {
        staffChat @0 () -> (result :Result(Chat, Text));
        ban @1 (name :Text) -> (result :Result(Ref(Bool), Text));
        unban @2 (name :Text) -> (result :Result(Ref(Bool), Text));
    }

    interface AdministratorSession extends (ModeratorSession) {
        restart @0 ();
    }

    interface RootSession extends (AdministratorSession) {
        shutdown @0 ();
    }

    login @0 (username :Text, password :Text) -> (result :Result(Session, Text));
}
