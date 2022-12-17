#include <phansar/common/reflect/debug_visitor.hpp>

namespace phansar::common::reflect {
struct debug_visitor::impl {};

debug_visitor::debug_visitor()                             = default;

debug_visitor::debug_visitor(const debug_visitor & _other) = default;

auto debug_visitor::operator=(const debug_visitor & _other)
    -> debug_visitor &                                         = default;

debug_visitor::debug_visitor(debug_visitor && _other) noexcept = default;

auto debug_visitor::operator=(debug_visitor && _other) noexcept
    -> debug_visitor &          = default;

debug_visitor::~debug_visitor() = default;
} // namespace phansar::common::reflect
