#include <phansar/test/fixture/executor_fixture.hpp>

namespace phansar::test::fixture {
template <class T>
executor_fixture<T>::executor_fixture() {
  common::g_service_container.emplace<common::service::executor_service>();

  // NOLINTNEXTLINE(cppcoreguidelines-prefer-member-initializer)
  executor =
      &common::g_service_container.service<common::service::executor_service>();
}

template <class T>
executor_fixture<T>::executor_fixture(const executor_fixture & _other) =
    default;

template <class T>
auto executor_fixture<T>::operator=(const executor_fixture & _other)
    -> executor_fixture<T> & = default;

template <class T>
executor_fixture<T>::executor_fixture(executor_fixture && _other) noexcept =
    default;

template <class T>
auto executor_fixture<T>::operator=(executor_fixture && _other) noexcept
    -> executor_fixture<T> & = default;

template <class T>
executor_fixture<T>::~executor_fixture() {
  executor->wait_for_all();
}
} // namespace phansar::test::fixture
