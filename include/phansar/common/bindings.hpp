#ifndef PHANSAR_COMMON_BINDINGS_HPP
#define PHANSAR_COMMON_BINDINGS_HPP

#include <phansar/vendor/json.hpp>
#include <phansar/vendor/rttr.hpp>

namespace rttr {
void to_json(nlohmann::ordered_json & _json, const instance & _obj);
}

#endif
