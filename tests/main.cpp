#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>
#include <common/core/core.hpp>
#include <common/scopes/scopes.hpp>

using namespace common;

int main(int argc, char *argv[]) {
    scopes::plibsys guard1;
    scopes::enet guard2;

    return Catch::Session().run(argc, argv);
}
