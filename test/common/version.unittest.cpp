#include <phansar/common/version.hpp>
#include <catch2/catch.hpp>

TEST_CASE("common::version", "[common][version]") {
    REQUIRE(! phansar::common::version::k_version.empty());
    REQUIRE(! phansar::common::version::k_major.empty());
    REQUIRE(! phansar::common::version::k_minor.empty());
    REQUIRE(! phansar::common::version::k_patch.empty());
    REQUIRE(! phansar::common::version::k_type.empty());
    REQUIRE(! phansar::common::version::k_timestamp.empty());
    REQUIRE(! phansar::common::version::k_git_branch.empty());
    REQUIRE(! phansar::common::version::k_git_hash.empty());
    REQUIRE(! phansar::common::version::k_git_short_hash.empty());
    REQUIRE(! phansar::common::version::k_git_changes.empty());
}
