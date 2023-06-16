//
// Created by Arya Rakha on 6/5/2023.
//

#include <iostream>
#include <random>
#include "GameScene.h"
#include "../systems/LocalPlayerMovementSystem.h"
#include "../systems/SFMLRenderSystem.h"
#include "../components/LocalPlayer.h"
#include "../components/PhysicsDefinition.h"
#include "../systems/Box2DPhysicsSystem.h"
#include "imgui.h"
#include "../components/SFMLDrawable.h"
#include "../components/SFMLTransformable.h"
#include "../systems/SFMLSpriteSystem.h"
#include "../systems/Box2DDebugDrawSystem.h"
#include "../components/Sprite.h"
#include "../Application.h"
#include "../systems/WrapAroundSystem.h"
#include "../components/WrapAround.h"

void GameScene::RegisterSystems(SystemsHandler *handle) {
    handle->RegisterSystem(new Box2DPhysicsSystem());
    handle->RegisterSystem(new LocalPlayerMovementSystem());
    handle->RegisterSystem(new SFMLRenderSystem());
    handle->RegisterSystem(new SFMLSpriteSystem());
    handle->RegisterSystem(new Box2DDebugDrawSystem());
    handle->RegisterSystem(new WrapAroundSystem());
}

void GameScene::OnStart() {

    auto width = Application::Width;
    auto height = Application::Height;

    gameView.setCenter(0.0f, 0.0f);
    gameView.setSize(width, height);

    CreatePlayer();

    std::random_device dev;
    std::mt19937 rng(dev());

    for (int i = 0; i < 300; ++i) {
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

bool showWindow = false;

void GameScene::OnUpdate() {
    ImGui::ShowDemoWindow(&showWindow);
}

void GameScene::OnFixedUpdate() {

}

void GameScene::OnRender(sf::RenderTarget *renderTarget) {
    renderTarget->setView(gameView);
}

void GameScene::CreatePlayer() {
    auto player = registry.create();

    registry.emplace<SpriteDefinition>(player, SpriteDefinition {"playerShip1_blue", 1, -90.f, 0.3f});

    registry.emplace<Box2DDebugDefinition>(player, Box2DDebugDefinition { sf::Color::Green, 2.f});

    registry.emplace<WrapAround>(player, WrapAround {});
    registry.emplace<MoveSpeed>(player, MoveSpeed {10.0f});
    registry.emplace<SpinSpeed>(player, SpinSpeed {6.0f});
    registry.emplace<LocalPlayer>(player, LocalPlayer{});
    registry.emplace<Position>(player, Position {Vector2(0.0f, 0.0f)});
    registry.emplace<Rotation>(player, Rotation {0.0f});

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 1.0f;

    auto rect = new b2PolygonShape;
    rect->SetAsBox(15.f * 0.01f, 8.f * 0.01f);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.1f;
    fixtureDef.shape = rect;
    fixtureDef.userData.pointer = static_cast<std::uintptr_t>(player);

    registry.emplace<PhysicsDefinition>(player, PhysicsDefinition {bodyDef, fixtureDef, rect});
}

void GameScene::CreateAsteroid(float size, float x, float y, float rotation) {
    auto asteroid = registry.create();

    float halfSize = size/2.f;

    sf::RectangleShape shape;
    shape.setSize(Vector2(size, size));
    shape.setOrigin(halfSize, halfSize);
    shape.setFillColor(sf::Color{255, 0, 0});

    auto pShape = std::make_shared<sf::RectangleShape>(shape);

    registry.emplace<WrapAround>(asteroid, WrapAround {});
    registry.emplace<SFMLDrawable>(asteroid, SFMLDrawable {0, pShape});
    registry.emplace<SFMLTransformable>(asteroid, SFMLTransformable {pShape});
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
