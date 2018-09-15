#include <catch2/catch.hpp>
#include <common/scopes/sdl_scope.hpp>

using namespace common::scopes;

TEST_CASE("can create sdl scopes", "[libs][common][scopes][sdl]") {
    sdl_scope ss(SDL_INIT_EVERYTHING);
    REQUIRE(ss.get_guards() == 1);

    sdl_image_scope sis(IMG_INIT_PNG);
    REQUIRE(sis.get_guards() == 1);

    sdl_mixer_scope sms(MIX_INIT_OGG);
    REQUIRE(sms.get_guards() == 1);

    sdl_ttf_scope sts;
    REQUIRE(sts.get_guards() == 1);
}
