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

#include <catch2/catch.hpp>
#include <common/scopes/sdl_scope.hpp>

using namespace common::scopes;

TEST_CASE("can create sdl scopes", "[libs][common][scopes][sdl]") {
    // sdl_scope ss(SDL_INIT_EVERYTHING);
    // REQUIRE(ss.get_guards() == 1);

    sdl_image_scope sis(IMG_INIT_PNG);
    REQUIRE(sis.get_guards() == 1);

    // sdl_mixer_scope sms(MIX_INIT_OGG);
    // REQUIRE(sms.get_guards() == 1);

    sdl_ttf_scope sts;
    REQUIRE(sts.get_guards() == 1);
}
