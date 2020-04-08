#include <common.hpp>

auto main(int argc, char *argv[]) -> int {
    common::system::init(argc, argv);

    common::system::shutdown();

    return 0;
}
