#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>
#include <string>

#ifdef TESTING_PH_COMMON_SYSTEM
#    include "common_system.hpp"
#else
#    include <common_system.hpp>
#endif

int main(int argc, char *argv[]) {
    common::system::init(argc, argv);

    auto result = Catch::Session().run(argc, argv);

    common::system::shutdown();

    return result;
}
