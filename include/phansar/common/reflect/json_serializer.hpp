#ifndef PHANSAR_COMMON_REFLECT_JSON_SERIALIZER_HPP
#define PHANSAR_COMMON_REFLECT_JSON_SERIALIZER_HPP

#include <nlohmann/json.hpp>
#include <rttr/type>

namespace rttr {
void to_json(nlohmann::json & _json, instance const & _obj);

void from_json(nlohmann::json const & _json, instance & _obj);
} // namespace rttr

#endif
