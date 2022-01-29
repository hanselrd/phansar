#include <phansar/common/errc.hpp>
#include <rttr/registration>

namespace {
struct error_category : std::error_category {
    [[nodiscard]] auto name() const noexcept -> const char * override;
    [[nodiscard]] auto message(int _condition) const -> std::string override;
};

auto error_category::name() const noexcept -> const char * {
    return "raw generic error";
}

auto error_category::message(int _condition) const -> std::string {
    using namespace phansar::common;

    switch (static_cast<errc>(_condition)) {
    case errc::error100:
        return "error 100";
    case errc::error101:
        return "error 101";
    case errc::error102:
        return "error 102";
    case errc::error200:
        return "error 200";
    case errc::error300:
        return "error 300";
    case errc::error400:
        return "error 400";
    case errc::error500:
        return "error 500";
    default:
        return "(unknown)";
    }
}

const auto k_error_category = error_category{};
} // namespace

namespace phansar::common {
auto make_error_code(errc _e) -> std::error_code {
    return {static_cast<int>(_e), k_error_category};
}

/* [[[cog
import rttr
rttr.Rttr.builder() \
    .enumerations([ \
        rttr.RttrEnum.builder() \
            .name("errc") \
            .type("errc") \
            .values([ \
                "error100", \
                "error101", \
                "error102", \
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
    rttr::registration::enumeration<errc>("errc")(
        rttr::value("error100", errc::error100),
        rttr::value("error101", errc::error101),
        rttr::value("error102", errc::error102),
        rttr::value("error200", errc::error200),
        rttr::value("error300", errc::error300),
        rttr::value("error400", errc::error400),
        rttr::value("error500", errc::error500)
    );
}
// clang-format on
// NOLINTEND
/* [[[end]]] */
} // namespace phansar::common
