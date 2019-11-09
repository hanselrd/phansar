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

#include <common/utils/log/log.hpp>
#include <rttr/registration>

struct MyStruct {
    MyStruct() {
    }

    void func(double) {
    }

    int data;
};

RTTR_REGISTRATION {
    rttr::registration::class_<MyStruct>("MyStruct")
        .constructor<>()
        .property("data", &MyStruct::data)
        .method("func", &MyStruct::func);
}

int main(int argc, char *argv[]) {
    common::utils::log::init("rttr_test.log");

    {
        auto t = rttr::type::get<MyStruct>();

        for (auto &prop : t.get_properties()) {
            LOGI("name: {}", prop.get_name());
        }

        for (auto &meth : t.get_methods()) {
            LOGI("name: {}", meth.get_name());
        }
    }

    {
        auto t = rttr::type::get_by_name("MyStruct");
        auto var = t.create();

        auto ctor = t.get_constructor();
        var = ctor.invoke();
        LOGI("{}", var.get_type().get_name());
    }

    {
        MyStruct obj;

        auto prop = rttr::type::get(obj).get_property("data");
        prop.set_value(obj, 23);

        auto var_prop = prop.get_value(obj);
        LOGI("{}", var_prop.to_int());
    }

    {
        MyStruct obj;

        auto meth = rttr::type::get(obj).get_method("func");
        meth.invoke(obj, 42.0);

        auto var = rttr::type::get(obj).create();
        meth.invoke(var, 42.0);
    }

    return 0;
}
