#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>

auto main(int _argc, char * _argv[]) -> int {
    return Catch::Session().run(_argc, _argv);
}
