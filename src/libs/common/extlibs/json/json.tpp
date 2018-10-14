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

#ifndef COMMON_EXTLIBS_JSON_TPP
#define COMMON_EXTLIBS_JSON_TPP

#include "json.hpp"

namespace nlohmann {
template <class T>
void adl_serializer<std::optional<T>>::to_json(json &j, const std::optional<T> &opt) {
    if (opt.has_value()) {
        j = *opt;
    } else {
        j = nullptr;
    }
}

template <class T>
void adl_serializer<std::optional<T>>::from_json(const json &j, std::optional<T> &opt) {
    if (j.is_null()) {
        opt = std::nullopt;
    } else {
        opt = j.get<T>();
    }
}

namespace detail {
template <std::size_t N> struct variant_switch {
    template <class V> void operator()(std::size_t index, const json &value, V &v) const {
        if (index == N) {
            v = value.get<std::variant_alternative_t<N, V>>();
        } else {
            variant_switch<N - 1>{}(index, value, v);
        }
    }
};

template <> struct variant_switch<0> {
    template <class V> void operator()(std::size_t index, const json &value, V &v) const {
        if (index == 0) {
            v = value.get<std::variant_alternative_t<0, V>>();
        }
    }
};
} // namespace detail

template <class... Ts>
void adl_serializer<std::variant<Ts...>>::to_json(json &j, const std::variant<Ts...> &var) {
    std::visit(
        [&](auto &&value) {
            j["index"] = var.index();
            j["value"] = std::forward<decltype(value)>(value);
        },
        var);
}

template <class... Ts>
void adl_serializer<std::variant<Ts...>>::from_json(const json &j, std::variant<Ts...> &var) {
    const auto index = j["index"].get<int>();
    detail::variant_switch<sizeof...(Ts) - 1>{}(index, j["value"], var);
}
} // namespace nlohmann

#endif
