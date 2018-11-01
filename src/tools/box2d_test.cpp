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

#include <Box2D/Box2D.h>
#include <common/utils/log/log.hpp>
#include <cstdint>

int main(int argc, char *argv[]) {
    common::utils::log::init("box2d_test.log");

    auto gravity = b2Vec2{0.f, -10.f};

    auto world = b2World{gravity};

    auto groundBodyDef = b2BodyDef{};
    groundBodyDef.position.Set(0.f, -10.f);

    auto groundBody = world.CreateBody(&groundBodyDef);

    auto groundBox = b2PolygonShape{};
    groundBox.SetAsBox(50.f, 10.f);

    groundBody->CreateFixture(&groundBox, 0.f);

    auto bodyDef = b2BodyDef{};
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.f, 4.f);
    auto body = world.CreateBody(&bodyDef);

    auto dynamicBox = b2PolygonShape{};
    dynamicBox.SetAsBox(1.f, 1.f);

    auto fixtureDef = b2FixtureDef{};
    fixtureDef.shape = &dynamicBox;

    fixtureDef.density = 1.f;

    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);

    auto timeStep = float{1.f / 60.f};
    auto velocityIterations = std::int32_t{6};
    auto positionIterations = std::int32_t{2};

    for (auto i = std::int32_t{0}; i < 60; ++i) {
        world.Step(timeStep, velocityIterations, positionIterations);

        auto position = body->GetPosition();
        auto angle = body->GetAngle();

        LOGI << position.x << " " << position.y << " " << angle;
    }

    return 0;
}
