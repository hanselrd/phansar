#ifndef PHANSAR_COMMON_ERRC_HPP
#define PHANSAR_COMMON_ERRC_HPP

#include <system_error>

namespace phansar::common {
enum class errc {
  error100 = 100,
  error101 = 101,
  error102 = 102,
  error200 = 200,
  error300 = 300,
  error400 = 400,
  error500 = 500,
};

auto make_error_code(errc _e) -> std::error_code;
} // namespace phansar::common

namespace std {
template <>
struct is_error_code_enum<phansar::common::errc> : std::true_type {};
} // namespace std

#endif
