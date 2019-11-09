/**
 * This file is part of Phansar.
 *
 * Copyright (C) 2018  Hansel De La Cruz
 *
 * Phansar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Phansar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with Phansar.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBS_COMMON_EXTLIBS_JSON_JSON_HPP
#define LIBS_COMMON_EXTLIBS_JSON_JSON_HPP

#include <nlohmann/json.hpp>
#include <optional>
#include <variant>

namespace nlohmann {
template <class T> struct adl_serializer<std::optional<T>> {
    static void to_json(json &j, const std::optional<T> &opt);
    static void from_json(const json &j, std::optional<T> &opt);
};

template <class... Ts> struct adl_serializer<std::variant<Ts...>> {
    static void to_json(json &j, const std::variant<Ts...> &var);
    static void from_json(const json &j, std::variant<Ts...> &var);
};
} // namespace nlohmann

namespace common {
namespace extlibs {
using namespace nlohmann;
}
} // namespace common

#include "json.tpp"

#endif
