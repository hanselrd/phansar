#include <phansar/common/errc.hpp>
#include <phansar/common/error.hpp>
#include <rttr/registration>

namespace {
struct error_category : std::error_category {
  [[nodiscard]] auto name() const noexcept -> const char * override;
  [[nodiscard]] auto message(int _condition) const -> std::string override;
  [[nodiscard]] auto equivalent(const std::error_code & _code,
                                int _condition) const noexcept -> bool override;
};

auto error_category::name() const noexcept -> const char * {
  return "generic error";
}

auto error_category::message(int _condition) const -> std::string {
  using namespace phansar::common;

  switch (static_cast<error>(_condition)) {
  case error::error100:
    return "error 100";
  case error::error200:
    return "error 200";
  case error::error300:
    return "error 300";
  case error::error400:
    return "error 400";
  case error::error500:
    return "error 500";
  default:
    return "(unknown)";
  }
}

auto error_category::equivalent(const std::error_code & _code,
                                int _condition) const noexcept -> bool {
  using namespace phansar::common;

  const auto & error_category = std::error_code{errc{}}.category();

  switch (static_cast<error>(_condition)) {
  case error::error100:
    return _code.category() == error_category && _code.value() >= 100 &&
           _code.value() < 200;
  case error::error200:
    return _code.category() == error_category && _code.value() >= 200 &&
           _code.value() < 300;
  case error::error300:
    return _code.category() == error_category && _code.value() >= 300 &&
           _code.value() < 400;
  case error::error400:
    return _code.category() == error_category && _code.value() >= 400 &&
           _code.value() < 500;
  case error::error500:
    return _code.category() == error_category && _code.value() >= 500 &&
           _code.value() < 600;
  default:
    return false;
  }
}

const auto k_error_category = error_category{};
} // namespace

namespace phansar::common {
auto make_error_condition(error _e) -> std::error_condition {
  return {static_cast<int>(_e), k_error_category};
}

/* [[[cog
import rttr
rttr.Rttr.builder() \
    .enumerations([ \
        rttr.RttrEnum.builder() \
            .name("error") \
            .type("error") \
            .values([ \
                "error100", \
                "error200", \
                "error300", \
                "error400", \
                "error500", \
            ]) \
            .build(), \
    ]) \
    .build() \
    .dump()
]]] */
// NOLINTBEGIN
// clang-format off
RTTR_REGISTRATION {
    rttr::registration::enumeration<error>("error")(
        rttr::value("error100", error::error100),
        rttr::value("error200", error::error200),
        rttr::value("error300", error::error300),
        rttr::value("error400", error::error400),
        rttr::value("error500", error::error500)
    );
}
// clang-format on
// NOLINTEND
/* [[[end]]] */
} // namespace phansar::common
