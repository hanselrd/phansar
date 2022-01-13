#ifndef PHANSAR_COMMON_ERROR_HPP
#define PHANSAR_COMMON_ERROR_HPP

#include <system_error>

namespace phansar::common {
enum class error {
    error100,
    error200,
    error300,
    error400,
    error500,
};

auto make_error_condition(error _e) -> std::error_condition;
} // namespace phansar::common

namespace std {
template <>
struct is_error_condition_enum<phansar::common::error> : std::true_type {};
} // namespace std

#endif
