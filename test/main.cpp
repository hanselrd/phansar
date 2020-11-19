#include <phansar/common/system.hpp>

#define CATCH_CONFIG_RUNNER
#include <phansar/vendor/catch2.hpp>

auto main(int _argc, char * _argv[]) -> int {
    phansar::common::system::init(_argc, _argv, false);

    auto result = Catch::Session().run(_argc, _argv);

    phansar::common::system::shutdown();

    return result;
}
