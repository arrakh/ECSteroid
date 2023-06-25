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
#include "../components/ShootAbility.h"
#include "../systems/PlayerShootSystem.h"
#include "../systems/DebugAngleSystem.h"
#include "../systems/BulletLifetimeSystem.h"
#include "../systems/BulletCollisionSystem.h"

void GameScene::RegisterSystems(SystemsHandler *handle) {
    handle->RegisterSystem(new Box2DPhysicsSystem());
    handle->RegisterSystem(new LocalPlayerMovementSystem());
    handle->RegisterSystem(new SFMLRenderSystem());
    handle->RegisterSystem(new SFMLSpriteSystem());
    handle->RegisterSystem(new Box2DDebugDrawSystem());
    handle->RegisterSystem(new WrapAroundSystem());
    handle->RegisterSystem(new PlayerShootSystem());
    handle->RegisterSystem(new BulletLifetimeSystem());
    handle->RegisterSystem(new BulletCollisionSystem());
}

void GameScene::OnStart() {

    auto width = Application::Width;
    auto height = Application::Height;

    gameView.setCenter(0.0f, 0.0f);
    gameView.setSize(width, height);

    CreateBackground();

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

    Vector2 size{16.f, 30.f};

    registry.emplace<SpriteDefinition>(player, SpriteDefinition {
        .spriteName =  "playerShip1_blue", .initialOrder =  1, .initialAngle = 90.f,
        .useCustomDimensions = true, .customWidth = size.y, .customHeight = size.x
    });

    registry.emplace<Box2DDebugDefinition>(player, Box2DDebugDefinition { sf::Color::Green, 1.f});

    registry.emplace<WrapAround>(player, WrapAround {});
    registry.emplace<LocalPlayer>(player, LocalPlayer{});
    registry.emplace<Position>(player, Position {Vector2(0.0f, 0.0f)});
    registry.emplace<Rotation>(player, Rotation {0.0f});

    registry.emplace<MoveSpeed>(player, MoveSpeed {10.0f});
    registry.emplace<SpinSpeed>(player, SpinSpeed {6.0f});
    registry.emplace<ShootAbility>(player, ShootAbility { size.x / 2.f + 6.f,  0.3f, 300.f, 1.f, 5.f });

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 1.0f;

    auto rect = new b2PolygonShape;
    rect->SetAsBox(size.x / 2.f * 0.01f, size.y / 2.f * 0.01f);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.1f;
    fixtureDef.shape = rect;
    fixtureDef.userData.pointer = static_cast<std::uintptr_t>(player);

    registry.emplace<PhysicsDefinition>(player, PhysicsDefinition {bodyDef, fixtureDef, rect});
}

void GameScene::CreateAsteroid(float size, float x, float y, float rotation) {
    auto asteroid = registry.create();

    registry.emplace<SpriteDefinition>(asteroid, SpriteDefinition {
            .spriteName =  "meteorBrown_big4", .initialOrder =  0,
            .useCustomDimensions = true, .customWidth = size, .customHeight = size
    });

    registry.emplace<Box2DDebugDefinition>(asteroid, Box2DDebugDefinition { sf::Color::Green, 1.f});

    registry.emplace<WrapAround>(asteroid, WrapAround {});
    registry.emplace<Position>(asteroid, Position {Vector2(x, y)});
    registry.emplace<Rotation>(asteroid, Rotation {rotation});

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 0.0f;
    bodyDef.position = Vector2(x, y);
    bodyDef.angle = rotation * b2_pi / 180.0f;

    auto shape = new b2CircleShape;
    shape->m_radius = size * 0.01f / 2.f;

    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.2f;
    fixtureDef.friction = 0.1f;
    fixtureDef.shape = shape;
    fixtureDef.userData.pointer = static_cast<std::uintptr_t>(asteroid);

    registry.emplace<PhysicsDefinition>(asteroid, PhysicsDefinition {bodyDef, fixtureDef, shape});
}

void GameScene::CreateBackground() {
    auto bg = registry.create();

    registry.emplace<Position>(bg, Position {Vector2(0, 0)});
    registry.emplace<SpriteDefinition>(bg, SpriteDefinition {
            .spriteName =  "darkPurple", .initialOrder =  -10000, .center = true,
            .useCustomDimensions = true, .customWidth = Application::Width, .customHeight = Application::Height,
            .tiled = true
    });
}
