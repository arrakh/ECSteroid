//
// Created by Arya Rakha on 6/5/2023.
//

#include <iostream>
#include <random>
#include "GameScene.h"
#include "../systems/LocalPlayerMovementSystem.h"
#include "../systems/RectangleDrawSystem.h"
#include "../components/SFMLRectShape.h"
#include "../components/LocalPlayer.h"
#include "../components/PhysicsDefinition.h"
#include "../systems/Box2DPhysicsSystem.h"
#include "imgui.h"
#include "../Constants.h"

void GameScene::RegisterSystems(SystemsHandler *handle) {
    handle->RegisterSystem(new Box2DPhysicsSystem());
    handle->RegisterSystem(new LocalPlayerMovementSystem());
    handle->RegisterSystem(new RectangleDrawSystem());
}

void GameScene::OnStart() {

    auto width = Constants::DEFAULT_SCREEN_WIDTH_F;
    auto height = Constants::DEFAULT_SCREEN_HEIGHT_F;

    gameView.setCenter(0.0f, 0.0f);
    gameView.setSize(width, height);

    CreatePlayer();

    std::random_device dev;
    std::mt19937 rng(dev());

    for (int i = 0; i < 200; ++i) {
        std::uniform_real_distribution<float> randSize(20,50);
        float size = randSize(rng);
        float doubleSize = size * 2;

        float hw = width/2.f;
        float hh = height/2.f;

        std::uniform_real_distribution<float> randPosX(-hw + doubleSize ,hw - doubleSize);
        std::uniform_real_distribution<float> randPosY(-hh + doubleSize ,hh - doubleSize);

        std::uniform_real_distribution<float> randRot(0.f,360.f);

        CreateAsteroid(size, randPosX(rng), randPosY(rng), randRot(rng));
    }
}

void GameScene::OnUpdate() {
    ImGui::ShowDemoWindow();
}

void GameScene::OnFixedUpdate() {

}

void GameScene::OnRender(sf::RenderTarget *renderTarget) {
    renderTarget->setView(gameView);
}

void GameScene::CreatePlayer() {
    auto player = registry.create();

    SFMLRectShape shape;
    shape.shape.setSize(Vector2(60.f, 40.f));
    shape.shape.setOrigin(30.0f, 20.0f);
    shape.shape.setFillColor(sf::Color{0, 0, 255});

    registry.emplace<SFMLRectShape>(player, shape);
    registry.emplace<MoveSpeed>(player, MoveSpeed {100.0f});
    registry.emplace<SpinSpeed>(player, SpinSpeed {2.0f});
    registry.emplace<LocalPlayer>(player, LocalPlayer{});
    registry.emplace<Position>(player, Position {Vector2(0.0f, 0.0f)});
    registry.emplace<Rotation>(player, Rotation {0.0f});

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 1.0f;

    auto rect = new b2PolygonShape;
    rect->SetAsBox(30.f * 0.01f, 20.f * 0.01f);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.1f;
    fixtureDef.shape = rect;
    fixtureDef.userData.pointer = static_cast<std::uintptr_t>(player);

    registry.emplace<PhysicsDefinition>(player, PhysicsDefinition {bodyDef, fixtureDef, rect});
}

void GameScene::CreateAsteroid(float size, float x, float y, float rotation) {
    auto asteroid = registry.create();

    std::cout << "Will put x: " << x << " y: " << y << std::endl;

    SFMLRectShape shape;

    float halfSize = size/2.f;

    shape.shape.setSize(Vector2(size, size));
    shape.shape.setOrigin(halfSize, halfSize);
    shape.shape.setFillColor(sf::Color{255, 0, 0});

    registry.emplace<SFMLRectShape>(asteroid, shape);
    registry.emplace<Position>(asteroid, Position {Vector2(x, y)});
    registry.emplace<Rotation>(asteroid, Rotation {rotation});

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 0.0f;
    bodyDef.position = Vector2(x, y);
    bodyDef.angle = rotation * b2_pi / 180.0f;

    auto rect = new b2PolygonShape;
    rect->SetAsBox(halfSize * 0.01f, halfSize * 0.01f);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.2f;
    fixtureDef.friction = 0.1f;
    fixtureDef.shape = rect;
    fixtureDef.userData.pointer = static_cast<std::uintptr_t>(asteroid);

    registry.emplace<PhysicsDefinition>(asteroid, PhysicsDefinition {bodyDef, fixtureDef, rect});
}
