#include <catch2/catch.hpp>
#include <common/scopes/enet_scope.hpp>

using namespace common::scopes;

TEST_CASE("can create enet scope", "[libs][common][scopes][enet]") {
    enet_scope es;
    REQUIRE(es.get_guards() == 2);
}
