//
// Created by Arya Rakha on 6/5/2023.
//

#include <iostream>
#include "TestScene.h"
#include "../systems/LocalPlayerMovementSystem.h"
#include "../systems/RectangleDrawSystem.h"
#include "../components/SFMLRectangleShape.h"
#include "../components/Speed.h"
#include "../components/Position.h"
#include "../components/LocalPlayer.h"

void TestScene::RegisterSystems(SystemsHandler *handle) {
    handle->RegisterSystem(new LocalPlayerMovementSystem());
    handle->RegisterSystem(new RectangleDrawSystem());
}

void TestScene::OnStart() {
    auto player = registry.create();

    SFMLRectangleShape shape;
    shape.shape.setSize(sf::Vector2f{100.0f, 100.0f});
    shape.shape.setFillColor(sf::Color{255, 0, 0});

    registry.emplace<SFMLRectangleShape>(player, shape);

    registry.emplace<Speed>(player, Speed {100.0f});
    registry.emplace<LocalPlayer>(player, LocalPlayer{});
    registry.emplace<Position>(player, Position {Vector2(0.0f, 0.0f)});
}

void TestScene::OnUpdate() {

}

void TestScene::OnFixedUpdate() {

}
