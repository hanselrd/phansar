@0x9c3b41026aa88468;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("phansar::common::schema");

using Transaction = import "transaction.capnp".Transaction;

#[[[cog
#   import cog
#   def transaction_chain(n: int) -> None:
#       if not (n >= 1):
#           cog.error("Transaction chain needs at least 1 argument")
#       cog.outl(f"struct TransactionChain{n}(")
#       for m in range(n):
#           cog.out(f"    Transaction{m}T")
#           cog.outl("," if m < n - 1 else ") {")
#       if n == 1:
#           m = n - 1
#           cog.outl(f"    transaction{m} @{m} :Transaction{m}T;")
#       else:
#           cog.outl("    union {")
#           for m in range(n):
#               cog.outl(f"        transaction{m} @{m} :Transaction{m}T;")
#           cog.outl("    }")
#       cog.outl("}")
#   for n in range(1, 11):
#       transaction_chain(n)
#]]]
struct TransactionChain1(
    Transaction0T) {
    transaction0 @0 :Transaction0T;
}
struct TransactionChain2(
    Transaction0T,
    Transaction1T) {
    union {
        transaction0 @0 :Transaction0T;
        transaction1 @1 :Transaction1T;
    }
}
struct TransactionChain3(
    Transaction0T,
    Transaction1T,
    Transaction2T) {
    union {
        transaction0 @0 :Transaction0T;
        transaction1 @1 :Transaction1T;
        transaction2 @2 :Transaction2T;
    }
}
struct TransactionChain4(
    Transaction0T,
    Transaction1T,
    Transaction2T,
    Transaction3T) {
    union {
        transaction0 @0 :Transaction0T;
        transaction1 @1 :Transaction1T;
        transaction2 @2 :Transaction2T;
        transaction3 @3 :Transaction3T;
    }
}
struct TransactionChain5(
    Transaction0T,
    Transaction1T,
    Transaction2T,
    Transaction3T,
    Transaction4T) {
    union {
        transaction0 @0 :Transaction0T;
        transaction1 @1 :Transaction1T;
        transaction2 @2 :Transaction2T;
        transaction3 @3 :Transaction3T;
        transaction4 @4 :Transaction4T;
    }
}
struct TransactionChain6(
    Transaction0T,
    Transaction1T,
    Transaction2T,
    Transaction3T,
    Transaction4T,
    Transaction5T) {
    union {
        transaction0 @0 :Transaction0T;
        transaction1 @1 :Transaction1T;
        transaction2 @2 :Transaction2T;
        transaction3 @3 :Transaction3T;
        transaction4 @4 :Transaction4T;
        transaction5 @5 :Transaction5T;
    }
}
struct TransactionChain7(
    Transaction0T,
    Transaction1T,
    Transaction2T,
    Transaction3T,
    Transaction4T,
    Transaction5T,
    Transaction6T) {
    union {
        transaction0 @0 :Transaction0T;
        transaction1 @1 :Transaction1T;
        transaction2 @2 :Transaction2T;
        transaction3 @3 :Transaction3T;
        transaction4 @4 :Transaction4T;
        transaction5 @5 :Transaction5T;
        transaction6 @6 :Transaction6T;
    }
}
struct TransactionChain8(
    Transaction0T,
    Transaction1T,
    Transaction2T,
    Transaction3T,
    Transaction4T,
    Transaction5T,
    Transaction6T,
    Transaction7T) {
    union {
        transaction0 @0 :Transaction0T;
        transaction1 @1 :Transaction1T;
        transaction2 @2 :Transaction2T;
        transaction3 @3 :Transaction3T;
        transaction4 @4 :Transaction4T;
        transaction5 @5 :Transaction5T;
        transaction6 @6 :Transaction6T;
        transaction7 @7 :Transaction7T;
    }
}
struct TransactionChain9(
    Transaction0T,
    Transaction1T,
    Transaction2T,
    Transaction3T,
    Transaction4T,
    Transaction5T,
    Transaction6T,
    Transaction7T,
    Transaction8T) {
    union {
        transaction0 @0 :Transaction0T;
        transaction1 @1 :Transaction1T;
        transaction2 @2 :Transaction2T;
        transaction3 @3 :Transaction3T;
        transaction4 @4 :Transaction4T;
        transaction5 @5 :Transaction5T;
        transaction6 @6 :Transaction6T;
        transaction7 @7 :Transaction7T;
        transaction8 @8 :Transaction8T;
    }
}
struct TransactionChain10(
    Transaction0T,
    Transaction1T,
    Transaction2T,
    Transaction3T,
    Transaction4T,
    Transaction5T,
    Transaction6T,
    Transaction7T,
    Transaction8T,
    Transaction9T) {
    union {
        transaction0 @0 :Transaction0T;
        transaction1 @1 :Transaction1T;
        transaction2 @2 :Transaction2T;
        transaction3 @3 :Transaction3T;
        transaction4 @4 :Transaction4T;
        transaction5 @5 :Transaction5T;
        transaction6 @6 :Transaction6T;
        transaction7 @7 :Transaction7T;
        transaction8 @8 :Transaction8T;
        transaction9 @9 :Transaction9T;
    }
}
#[[[end]]]
