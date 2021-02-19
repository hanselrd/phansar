#define CATCH_CONFIG_RUNNER
#include <phansar/vendor/catch2.hpp>

auto main(int _argc, char * _argv[]) -> int {
    return Catch::Session().run(_argc, _argv);
}
