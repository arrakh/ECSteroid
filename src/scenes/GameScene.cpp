//
// Created by Arya Rakha on 6/5/2023.
//

#include <iostream>
#include "GameScene.h"
#include "../systems/LocalPlayerMovementSystem.h"
#include "../systems/RectangleDrawSystem.h"
#include "../components/SFMLCircleShape.h"
#include "../components/LocalPlayer.h"
#include "../components/PhysicsDefinition.h"
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
    shape.shape.setSize(Vector2(60.f, 40.f));
    shape.shape.setOrigin(30.0f, 20.0f);
    shape.shape.setFillColor(sf::Color{255, 0, 0});

    registry.emplace<SFMLCircleShape>(player, shape);
    registry.emplace<MoveSpeed>(player, MoveSpeed {100.0f});
    registry.emplace<SpinSpeed>(player, SpinSpeed {2.0f});
    registry.emplace<LocalPlayer>(player, LocalPlayer{});
    registry.emplace<Position>(player, Position {Vector2(0.0f, 0.0f)});
    registry.emplace<Rotation>(player, Rotation {0.0f});

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 1.0f;

    auto circle = new b2CircleShape;
    circle->m_radius = 30.0f * 0.01;

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.1f;
    fixtureDef.shape = circle;
    fixtureDef.userData.pointer = static_cast<std::uintptr_t>(player);

    registry.emplace<PhysicsDefinition>(player, PhysicsDefinition {bodyDef, fixtureDef, circle});
}

void GameScene::OnUpdate() {

}

void GameScene::OnFixedUpdate() {

}

void GameScene::OnRender(sf::RenderTarget *renderTarget) {
    renderTarget->setView(gameView);
}
