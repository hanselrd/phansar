@0xd465f4b9563b7441;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("phansar::common::schema");

using Transaction = import "transaction.capnp".Transaction;

struct TransactionChain1(
    Transaction0) {
    transaction0 @0 :Transaction0;
}

struct TransactionChain2(
    Transaction0,
    Transaction1) {
    union {
        transaction0 @0 :Transaction0;
        transaction1 @1 :Transaction1;
    }
}

struct TransactionChain3(
    Transaction0,
    Transaction1,
    Transaction2) {
    union {
        transaction0 @0 :Transaction0;
        transaction1 @1 :Transaction1;
        transaction2 @2 :Transaction2;
    }
}

struct TransactionChain4(
    Transaction0,
    Transaction1,
    Transaction2,
    Transaction3) {
    union {
        transaction0 @0 :Transaction0;
        transaction1 @1 :Transaction1;
        transaction2 @2 :Transaction2;
        transaction3 @3 :Transaction3;
    }
}

struct TransactionChain5(
    Transaction0,
    Transaction1,
    Transaction2,
    Transaction3,
    Transaction4) {
    union {
        transaction0 @0 :Transaction0;
        transaction1 @1 :Transaction1;
        transaction2 @2 :Transaction2;
        transaction3 @3 :Transaction3;
        transaction4 @4 :Transaction4;
    }
}

struct TransactionChain6(
    Transaction0,
    Transaction1,
    Transaction2,
    Transaction3,
    Transaction4,
    Transaction5) {
    union {
        transaction0 @0 :Transaction0;
        transaction1 @1 :Transaction1;
        transaction2 @2 :Transaction2;
        transaction3 @3 :Transaction3;
        transaction4 @4 :Transaction4;
        transaction5 @5 :Transaction5;
    }
}

struct TransactionChain7(
    Transaction0,
    Transaction1,
    Transaction2,
    Transaction3,
    Transaction4,
    Transaction5,
    Transaction6) {
    union {
        transaction0 @0 :Transaction0;
        transaction1 @1 :Transaction1;
        transaction2 @2 :Transaction2;
        transaction3 @3 :Transaction3;
        transaction4 @4 :Transaction4;
        transaction5 @5 :Transaction5;
        transaction6 @6 :Transaction6;
    }
}

struct TransactionChain8(
    Transaction0,
    Transaction1,
    Transaction2,
    Transaction3,
    Transaction4,
    Transaction5,
    Transaction6,
    Transaction7) {
    union {
        transaction0 @0 :Transaction0;
        transaction1 @1 :Transaction1;
        transaction2 @2 :Transaction2;
        transaction3 @3 :Transaction3;
        transaction4 @4 :Transaction4;
        transaction5 @5 :Transaction5;
        transaction6 @6 :Transaction6;
        transaction7 @7 :Transaction7;
    }
}

struct TransactionChain9(
    Transaction0,
    Transaction1,
    Transaction2,
    Transaction3,
    Transaction4,
    Transaction5,
    Transaction6,
    Transaction7,
    Transaction8) {
    union {
        transaction0 @0 :Transaction0;
        transaction1 @1 :Transaction1;
        transaction2 @2 :Transaction2;
        transaction3 @3 :Transaction3;
        transaction4 @4 :Transaction4;
        transaction5 @5 :Transaction5;
        transaction6 @6 :Transaction6;
        transaction7 @7 :Transaction7;
        transaction8 @8 :Transaction8;
    }
}

struct TransactionChain10(
    Transaction0,
    Transaction1,
    Transaction2,
    Transaction3,
    Transaction4,
    Transaction5,
    Transaction6,
    Transaction7,
    Transaction8,
    Transaction9) {
    union {
        transaction0 @0 :Transaction0;
        transaction1 @1 :Transaction1;
        transaction2 @2 :Transaction2;
        transaction3 @3 :Transaction3;
        transaction4 @4 :Transaction4;
        transaction5 @5 :Transaction5;
        transaction6 @6 :Transaction6;
        transaction7 @7 :Transaction7;
        transaction8 @8 :Transaction8;
        transaction9 @9 :Transaction9;
    }
}
