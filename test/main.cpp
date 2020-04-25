#include <phansar/common/system.hpp>

#include <phansar/vendor/catch2_private.hpp>

#include <string>

auto main(int argc, char * argv[]) -> int {
    phansar::common::system::init(argc, argv, false);

    auto result = Catch::Session().run(argc, argv);

    phansar::common::system::shutdown();

    return result;
}
