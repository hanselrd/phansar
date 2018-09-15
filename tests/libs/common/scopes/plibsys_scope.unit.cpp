#include <catch2/catch.hpp>
#include <common/scopes/plibsys_scope.hpp>

using namespace common::scopes;

TEST_CASE("can create plibsys scope", "[libs][common][scopes][plibsys]") {
    plibsys_scope ps;
    REQUIRE(ps.get_guards() == 2);
}
