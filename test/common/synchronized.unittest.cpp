#include <phansar/common/policy/freestanding_implementation_policy.hpp>
#include <phansar/common/policy/hosted_implementation_policy.hpp>
#include <phansar/common/synchronized.hpp>
#include <phansar/test/fixture/executor_fixture.hpp>
#include <catch2/catch.hpp>

using namespace phansar;
using namespace phansar::common;

const auto k_iterations_per_worker = int{1'000};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays)
TEMPLATE_PRODUCT_TEST_CASE_METHOD(
    test::fixture::executor_fixture,
    "common::synchronized",
    "[common][synchronized][template][generate]",
    synchronized,
    (int,
     (int, policy::hosted_implementation_policy<int>),
     (int, policy::freestanding_implementation_policy<int>))) {
  auto s      = TestType{};

  auto addend = GENERATE(range<int>(1, 10));

  SECTION("locking allows thread safe modification") {
    for (auto i = std::size_t{0};
         i <
         (test::fixture::executor_fixture<TestType>::executor->num_workers() *
          k_iterations_per_worker);
         ++i) {
      test::fixture::executor_fixture<TestType>::executor->async([&]() {
        *s.lock() += addend;
      });
    }

    test::fixture::executor_fixture<TestType>::executor->wait_for_all();

    REQUIRE(
        *s.lock_shared() ==
        (static_cast<int>(test::fixture::executor_fixture<TestType>::executor
                              ->num_workers()) *
         k_iterations_per_worker * addend));
  }
}
