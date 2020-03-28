#include "ph_common_log.hpp"
#include <catch2/catch.hpp>

TEST_CASE("can initialize logger", "[libcommon][log]") {
    ph::common::log::init("unittest.log");
}
