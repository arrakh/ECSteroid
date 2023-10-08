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
#include "../application/Application.h"
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
#include "MenuScene.h"
#include "../systems/WaveSystem.h"
#include "../systems/EntityRelationSystem.h"
#include "../components/LocalPosition.h"
#include "../components/LocalRotation.h"
#include "../systems/ui/SFMLButtonSystem.h"
#include "../systems/ui/SFMLButtonStatesSpriteSystem.h"
#include "../systems/ui/SFMLButtonDebugDrawSystem.h"
#include "../systems/ui/SFMLTextSystem.h"
#include "../systems/tween/TweenSystems.h"
#include "../systems/tween/SFMLTweenSystems.h"
#include "../systems/TempMuzzleFlashSystem.h"

void GameScene::RegisterSystems(SystemsHandler *handle) {

    Tween::RegisterSystems(handle);
    Tween::RegisterSFMLSystems(handle);

    handle->Register(new EntityRelationSystem());
    handle->Register(new TempMuzzleFlashSystem()); //this is temp system because Entity Relation System broke
    handle->Register(new SFMLButtonSystem());
    handle->Register(new SFMLButtonStatesSpriteSystem());
    handle->Register(new WaveSystem());
    handle->Register(new AsteroidSpawnerSystem());
    handle->Register(new AsteroidScoreSystem());
    handle->Register(new Box2DPhysicsSystem());
    handle->Register(new LocalPlayerMovementSystem());
    handle->Register(new SFMLRenderSystem());
    handle->Register(new SFMLSpriteSystem());
    handle->Register(new SFMLTextSystem());
    //handle->Register(new Box2DDebugDrawSystem());
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
    sfWindow = std::dynamic_pointer_cast<SFMLWindow>(window);

    auto width = sfWindow->width;
    auto height = sfWindow->height;

    gameView.setCenter(0.0f, 0.0f);
    gameView.setSize(width, height);

    CreateBackground();

    CreatePlayer();
}

void GameScene::OnUpdate() {
    return;
    ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_FirstUseEver);

    static bool windowOpen;
    if (!ImGui::Begin("Game Scene", &windowOpen)){
        ImGui::End();
        return;
    }

    if (ImGui::Button("Quit To Menu")){
        Application::ChangeScene<MenuScene>();
    }

    ImGui::End();
}

void GameScene::OnFixedUpdate() {

}

void GameScene::OnRender() {
    sfWindow->windowPtr->setView(gameView);
}

void GameScene::CreatePlayer() {
    auto player = registry.create();

    Vector2 size{16.f, 30.f};

    registry.emplace<SpriteDefinition>(player, SpriteDefinition {
        .spriteName =  "playerShip", .initialOrder =  1,
        .useCustomDimensions = true, .customWidth = size.x, .customHeight = size.y
    });

    registry.emplace<Box2DDebugDefinition>(player, Box2DDebugDefinition { sf::Color::Green, 1.f});

    registry.emplace<WrapAround>(player, WrapAround {});
    registry.emplace<LocalPlayer>(player, LocalPlayer{});
    registry.emplace<WorldPosition>(player, WorldPosition {Vector2(0.0f, 0.0f)});
    registry.emplace<Rotation>(player, Rotation {0.0f});

    registry.emplace<MoveSpeed>(player, MoveSpeed {10.0f});
    registry.emplace<SpinSpeed>(player, SpinSpeed {6.0f});

    registry.emplace<Health>(player, Health{200.f});

    registry.emplace<ShootAbility>(player, ShootAbility {
        .startDistance = size.x / 2.f + 50.f,  .cooldown = 0.1f,
        .bulletSpeed = 1500.f, .bulletLifetime = 1.2f, .bulletDamage = 8.f
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

    registry.emplace<WorldPosition>(bg, WorldPosition {Vector2(0, 0)});
    registry.emplace<SpriteDefinition>(bg, SpriteDefinition {
            .spriteName =  "darkPurple", .initialOrder =  -10000,
            .useCustomDimensions = true, .customWidth = sfWindow->width, .customHeight = sfWindow->height,
            .tiled = true
    });
}
