//
// Created by Arya Rakha on 6/5/2023.
//

#include <iostream>
#include "GameScene.h"
#include "../systems/LocalPlayerMovementSystem.h"
#include "../systems/RectangleDrawSystem.h"
#include "../components/SFMLCircleShape.h"
#include "../components/Speed.h"
#include "../components/Position.h"
#include "../components/LocalPlayer.h"
#include "../components/PhysicsDefinition.h"
#include "../components/CircleShape.h"
#include "../systems/Box2DPhysicsSystem.h"

void GameScene::RegisterSystems(SystemsHandler *handle) {
    handle->RegisterSystem(new Box2DPhysicsSystem());
    handle->RegisterSystem(new LocalPlayerMovementSystem());
    handle->RegisterSystem(new RectangleDrawSystem());
}

void GameScene::OnStart() {
    gameView.setCenter(0.0f, 0.0f);
    gameView.setSize(1920u, 1080u);

    auto player = registry.create();

    SFMLCircleShape shape;
    shape.shape.setRadius(50.f);
    shape.shape.setFillColor(sf::Color{255, 0, 0});

    registry.emplace<SFMLCircleShape>(player, shape);

    registry.emplace<CircleShape>(player, CircleShape {50.0f});
    registry.emplace<Speed>(player, Speed {10000.0f});
    registry.emplace<LocalPlayer>(player, LocalPlayer{});
    registry.emplace<Position>(player, Position {Vector2(0.0f, 0.0f)});

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;

    registry.emplace<PhysicsDefinition>(player, PhysicsDefinition {bodyDef, fixtureDef});
}

void GameScene::OnUpdate() {

}

void GameScene::OnFixedUpdate() {

}

void GameScene::OnRender(sf::RenderTarget *renderTarget) {
    renderTarget->setView(gameView);
}
