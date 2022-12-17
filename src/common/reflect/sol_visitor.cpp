#include <phansar/common/reflect/sol_visitor.hpp>

namespace phansar::common::reflect {
struct sol_visitor::impl {
  sol::state * state{};
  size_t       constructor_counter{};
};

sol_visitor::sol_visitor(sol::state & _state) : m_impl{&_state} {}

sol_visitor::sol_visitor(const sol_visitor & _other) = default;

auto sol_visitor::operator=(const sol_visitor & _other)
    -> sol_visitor &                                     = default;

sol_visitor::sol_visitor(sol_visitor && _other) noexcept = default;

auto sol_visitor::operator=(sol_visitor && _other) noexcept
    -> sol_visitor &        = default;

sol_visitor::~sol_visitor() = default;

auto sol_visitor::_state_internal() const -> sol::state & {
  return *m_impl->state;
}

void sol_visitor::_constructor_counter_reset_internal() {
  m_impl->constructor_counter = 0;
}

auto sol_visitor::_constructor_counter_next_internal() -> std::size_t {
  return ++m_impl->constructor_counter;
}
} // namespace phansar::common::reflect
