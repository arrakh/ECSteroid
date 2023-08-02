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
#include "../systems/SFMLSpriteSystem.h"
#include "../systems/Box2DDebugDrawSystem.h"
#include "../components/Sprite.h"
#include "../Application.h"
#include "../systems/WrapAroundSystem.h"
#include "../components/WrapAround.h"
#include "../components/ShootAbility.h"
#include "../systems/PlayerShootSystem.h"
#include "../systems/BulletLifetimeSystem.h"
#include "../systems/BulletCollisionSystem.h"
#include "../systems/DestroyOnZeroHealthSystem.h"
#include "../systems/AsteroidSpawnerSystem.h"
#include "../datatype/CollisionGroup.h"
#include "../systems/ui/LocalPlayerHealthUISystem.h"
#include "../components/Health.h"
#include "../systems/AsteroidToPlayerCollisionSystem.h"
#include "../systems/ui/GameOverTextUISystem.h"
#include "../systems/AsteroidScoreSystem.h"
#include "../systems/ui/LocalScoreUISystem.h"
#include "../systems/GameBGMSystem.h"
#include "../systems/PlayerShootSFXSystem.h"

void GameScene::RegisterSystems(SystemsHandler *handle) {
    handle->Register(new AsteroidSpawnerSystem());
    handle->Register(new AsteroidScoreSystem());
    handle->Register(new Box2DPhysicsSystem());
    handle->Register(new LocalPlayerMovementSystem());
    handle->Register(new SFMLRenderSystem());
    handle->Register(new SFMLSpriteSystem());
    handle->Register(new Box2DDebugDrawSystem());
    handle->Register(new WrapAroundSystem());
    handle->Register(new PlayerShootSystem());
    handle->Register(new BulletLifetimeSystem());
    handle->Register(new BulletCollisionSystem());
    handle->Register(new AsteroidToPlayerCollisionSystem());
    handle->Register(new DestroyOnZeroHealthSystem());

    handle->Register(new GameBGMSystem());
    handle->Register(new PlayerShootSFXSystem());

    //UI Systems
    handle->Register(new LocalPlayerHealthUISystem());
    handle->Register(new GameOverTextUISystem());
    handle->Register(new LocalScoreUISystem());
}

void GameScene::OnStart() {

    auto width = Application::Width;
    auto height = Application::Height;

    gameView.setCenter(0.0f, 0.0f);
    gameView.setSize(width, height);

    CreateBackground();

    CreatePlayer();
}

void GameScene::OnUpdate() {
    ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_FirstUseEver);

    static bool windowOpen;
    if (!ImGui::Begin("Game Scene", &windowOpen)){
        ImGui::End();
        return;
    }

    if (ImGui::Button("Reset")){
        shouldEnd = true;
    }

    ImGui::End();
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

    registry.emplace<Health>(player, Health{200.f});

    registry.emplace<ShootAbility>(player, ShootAbility {
        .startDistance = size.x / 2.f + 10.f,  .cooldown = 0.2f,
        .bulletSpeed = 800.f, .bulletLifetime = 1.2f, .bulletDamage = 15.f
    });

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 1.0f;

    auto rect = new b2PolygonShape;
    rect->SetAsBox(size.x / 2.f * 0.01f, size.y / 2.f * 0.01f);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.1f;
    fixtureDef.shape = rect;
    fixtureDef.filter.categoryBits = CATEGORY_PLAYER;
    fixtureDef.userData.pointer = static_cast<std::uintptr_t>(player);

    registry.emplace<PhysicsDefinition>(player, PhysicsDefinition {bodyDef, fixtureDef, rect});
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
