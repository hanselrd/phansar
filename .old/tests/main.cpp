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

#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>
#include <string>

#ifdef TESTING_COMMON
#    include "../src/libs/common/scopes/enet_scope/enet_scope.hpp"
#    include "../src/libs/common/scopes/plibsys_scope/plibsys_scope.hpp"
#    include "../src/libs/common/utils/log/log.hpp"
#else
#    include <common/scopes/enet_scope/enet_scope.hpp>
#    include <common/scopes/plibsys_scope/plibsys_scope.hpp>
#    include <common/utils/log/log.hpp>
#endif

using namespace common;

int main(int argc, char *argv[]) {
    auto bin = std::string{argv[0]};

    utils::log::init(bin.substr(bin.find_last_of('/') + 1) + ".log");

    auto guard1 = scopes::plibsys_scope{};
    auto guard2 = scopes::enet_scope{};

    return Catch::Session().run(argc, argv);
}
