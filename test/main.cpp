#include <phansar/common/system.hpp>

#define CATCH_CONFIG_RUNNER
#include <phansar/vendor/catch2.hpp>

#include <string>

auto main(int argc, char * argv[]) -> int {
    phansar::common::system::init(argc, argv, false);

    auto result = Catch::Session().run(argc, argv);

    phansar::common::system::shutdown();

    return result;
}
