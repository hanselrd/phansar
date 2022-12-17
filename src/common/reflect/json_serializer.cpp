#include <phansar/common/macro.hpp>
#include <phansar/common/meta/y_combinator.hpp>
#include <phansar/common/reflect/json_serializer.hpp>
#include <variant>

namespace rttr {
void to_json(nlohmann::json & _json, const instance & _obj) {
  using namespace phansar::common;

  const auto write = meta::make_y_combinator(
      [](auto &&                                             _write,
         nlohmann::json &                                    _json,
         const std::variant<rttr::instance, rttr::variant> & _variant) -> void {
        PH_UNUSED(_write);
        PH_UNUSED(_json);
        PH_UNUSED(_variant);
      });

  write(_json, _obj);
}

void from_json(const nlohmann::json & _json, instance & _obj) {
  PH_UNUSED(_json);
  PH_UNUSED(_obj);
  PH_UNIMPLEMENTED();
}
} // namespace rttr
