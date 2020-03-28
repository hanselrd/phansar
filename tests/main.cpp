#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>
#include <string>

#ifdef TESTING_PH_COMMON_LOG
#    include "ph_common_log.hpp"
#else
#    include <ph_common_log.hpp>
#endif

int main(int argc, char *argv[]) {
    auto bin = std::string{argv[0]};

    ph::common::log::init(bin.substr(bin.find_last_of('/') + 1) + ".log");

    return Catch::Session().run(argc, argv);
}
