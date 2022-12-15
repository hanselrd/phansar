#include <catch2/catch.hpp>
#include <sigslot/signal.hpp>

TEST_CASE("vendor::sigslot", "[vendor][sigslot]") {
    auto sig  = sigslot::signal<>{};
    auto pass = false;

    sig.connect([&pass]() { pass = true; });

    REQUIRE(! pass);
    sig();
    REQUIRE(pass);
}
