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

#include <common/extlibs/json/json.hpp>
#include <common/utils/log/log.hpp>
#include <cstdint>
#include <optional>
#include <string>

struct person {
    std::string name;
    std::uint32_t age;
    std::optional<std::string> company;
};

void to_json(common::extlibs::json &j, const person &p) {
    j = common::extlibs::json{{"name", p.name}, {"age", p.age}, {"company", p.company}};
}

void from_json(const common::extlibs::json &j, person &p) {
    j.at("name").get_to(p.name);
    j.at("age").get_to(p.age);
    j.at("company").get_to(p.company);
}

int main(int argc, char *argv[]) {
    common::utils::log::init("optional_json.log");

    auto json = common::extlibs::json{{"test", nullptr}};
    LOGI(json.dump());
    auto test = json["test"].get<std::optional<std::uint32_t>>();
    LOGI(test.has_value());
    LOGI_IF(test.has_value(), test.value());

    auto p1 = person{"Bob", 18, "Google"};
    auto p2 = person{"Tod", 21};
    json["p1"] = p1;
    json["p2"] = p2;
    LOGI(json.dump());

    auto p1_copy = json["p1"].get<person>();
    auto p2_copy = json["p2"].get<person>();

    LOGI("p1.name: [{},{}]", p1.name, p1_copy.name);
    LOGI("p1.age: [{},{}]", p1.age, p1_copy.age);
    LOGI("p1.company: [{},{}]", p1.company.value_or("null"), p1_copy.company.value_or("null"));
    LOGI("p2.name: [{},{}]", p2.name, p2_copy.name);
    LOGI("p2.age: [{},{}]", p2.age, p2_copy.age);
    LOGI("p2.company: [{},{}]", p2.company.value_or("null"), p2_copy.company.value_or("null"));

    return 0;
}
