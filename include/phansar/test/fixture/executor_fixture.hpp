#ifndef PHANSAR_TEST_FIXTURE_EXECUTOR_FIXTURE_HPP
#define PHANSAR_TEST_FIXTURE_EXECUTOR_FIXTURE_HPP

#include <phansar/common/service/executor_service.hpp>
#include <phansar/common/service_container.hpp>

namespace phansar::test::fixture {
template <class T = void>
struct executor_fixture {
    executor_fixture();
    executor_fixture(const executor_fixture & _other);
    auto operator=(const executor_fixture & _other) -> executor_fixture &;
    executor_fixture(executor_fixture && _other) noexcept;
    auto operator=(executor_fixture && _other) noexcept -> executor_fixture &;
    virtual ~executor_fixture();

    tf::Executor * executor{};
};
} // namespace phansar::test::fixture

#include <phansar/test/fixture/executor_fixture.inl>

#endif
