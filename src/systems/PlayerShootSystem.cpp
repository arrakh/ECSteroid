//
// Created by rafizidny on 6/18/2023.
//

#include "PlayerShootSystem.h"
#include "../components/LocalPlayer.h"
#include "../util/Time.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../components/Rotation.h"
#include "../components/WorldPosition.h"
#include "../components/Sprite.h"
#include "../components/PhysicsDefinition.h"
#include "../components/debug/Box2DDebug.h"
#include "../components/bullet/BulletLifetime.h"
#include "../components/bullet/BulletDestroyOnCollision.h"
#include "../components/bullet/BulletDamage.h"
#include "../components/PhysicsBody.h"
#include "../datatype/CollisionGroup.h"
#include "../components/bullet/BulletOwner.h"
#include "../components/LocalPosition.h"
#include "EntityRelationSystem.h"
#include "../components/LocalRotation.h"
#include "imgui.h"
#include "../components/MuzzleFlash.h"
#include "../util/Tweens.h"
#include "../components/debug/DebugName.h"

void PlayerShootSystem::Update(entt::registry *registry) {

    auto muzzles = registry->view<MuzzleFlash>();
    for (auto [entity, muzzle] : muzzles.each()) {
        muzzle.timer -= Time::deltaTime();
        if (muzzle.timer > 0) continue;
        registry->remove<MuzzleFlash>(entity);
        std::cout << "WILL DESTROY " << DebugName::Get(registry, muzzle.muzzleEntity) << "\n";
        registry->destroy(muzzle.muzzleEntity);
    }

    auto cooldown = registry->view<ShootAbilityCooldown>();
    for (auto [entity, cooldownData] : cooldown.each()) {
        cooldownData.value -= Time::deltaTime();
        if (cooldownData.value <= 0.f) registry->remove<ShootAbilityCooldown>(entity);
    }

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) return;

    auto shoot = registry->view<ShootAbility, LocalPlayer, WorldPosition, Rotation>(entt::exclude<ShootAbilityCooldown>);
    for (auto [entity, shootData, pos, rot] : shoot.each()) {
        if (shootData.cooldown > 0.f) registry->emplace<ShootAbilityCooldown>(entity, ShootAbilityCooldown { shootData.cooldown });

        CreateBullet(entity, registry, pos.vector, rot.value, shootData);
        //CreateMuzzleFlash(entity, registry, pos.vector, rot.value, shootData);
    }
}

void PlayerShootSystem::Load(entt::registry *registry) {
    registry->sort<ShootAbility, ShootAbilityCooldown>();
}

void PlayerShootSystem::Unload() {

}

void PlayerShootSystem::CreateBullet(entt::entity shooter, entt::registry *registry, const Vector2 pos, const float angle, ShootAbility data) {
    auto bullet = registry->create();
    float size = 10.f;
    float halfSize = size / 2.f;

    registry->emplace<BulletOwner>(bullet, BulletOwner { shooter });
    registry->emplace<DebugName>(bullet, DebugName{ "Bullet #" + std::to_string(static_cast<std::uint32_t>(bullet))});
    registry->emplace<Box2DDebugDefinition>(bullet, Box2DDebugDefinition { sf::Color::Green, 1.f});

    float rad = angle * M_PI / 180;
    Vector2 shootDir {cos(rad) , sin(rad)};
    Vector2 bulletPos =  pos + (shootDir * (data.startDistance));

    registry->emplace<WorldPosition>(bullet, WorldPosition {bulletPos});
    registry->emplace<Rotation>(bullet, Rotation {angle});

    registry->emplace<BulletDestroyOnCollision>(bullet);

    if (data.bulletLifetime > 0.f) registry->emplace<BulletLifetime>(bullet, BulletLifetime { data.bulletLifetime});
    if (data.bulletDamage > 0.f) registry->emplace<BulletDamage>(bullet, BulletDamage { data.bulletDamage});

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 0.0f;
    bodyDef.position = bulletPos;
    bodyDef.angle = angle * b2_pi / 180.0f;
    bodyDef.bullet = true;

    auto shape = new b2CircleShape;
    shape->m_radius = size * 0.01f / 2.f;

    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.0001f;
    fixtureDef.friction = 0.f;
    fixtureDef.shape = shape;
    fixtureDef.userData.pointer = static_cast<std::uintptr_t>(bullet);

    float velIncrease = 0.f;

    auto shooterBody = registry->try_get<PhysicsBody>(shooter);
    if (shooterBody != nullptr) {
        auto vel = Vector2{shooterBody->body->GetLinearVelocity()};
        velIncrease = sqrt(vel.x * vel.x + vel.y * vel.y);
        fixtureDef.filter.maskBits = ~shooterBody->fixture->GetFilterData().categoryBits;
    }

    bodyDef.linearVelocity = shootDir * (data.bulletSpeed + velIncrease);

    registry->emplace<PhysicsDefinition>(bullet, PhysicsDefinition {bodyDef, fixtureDef, shape});

    //Visuals
    auto imageEntity = registry->create();
    registry->emplace<SpriteDefinition>(imageEntity, SpriteDefinition {
            .spriteName =  "bullet", .initialOrder =  0, .pivot = Vector2{0.780, 0.5},
            .useCustomDimensions = true, .customWidth = size * 11.3f, .customHeight = size * 4.3f,
    });

    registry->emplace<WorldPosition>(imageEntity, WorldPosition {bulletPos});
    registry->emplace<LocalPosition>(imageEntity, LocalPosition{Vector2(0,0)});
    registry->emplace<Rotation>(imageEntity, Rotation{angle});
    registry->emplace<LocalRotation>(imageEntity, LocalRotation{0});

    EntityRelationSystem::Assign(registry, bullet, imageEntity);
}

void PlayerShootSystem::CreateMuzzleFlash(entt::entity shooter, entt::registry *registry, const Vector2 pos, const float angle, ShootAbility data) {
    auto existingMuzzle = registry->try_get<MuzzleFlash>(shooter);
    if (existingMuzzle != nullptr){
        Tween::ResetTime(registry, existingMuzzle->opacityTween);
        Tween::ResetTime(registry, existingMuzzle->scaleTween);
        float time = existingMuzzle->totalTime;
        registry->patch<MuzzleFlash>(shooter, [time](MuzzleFlash &flash){ flash.timer = time; });
        return;
    }

    auto muzzle = registry->create();
    registry->emplace<SpriteDefinition>(muzzle, SpriteDefinition {
            .spriteName =  "muzzle-flash", .initialOrder =  10, .pivot = Vector2{0.142f, 0.5f},
            .useCustomDimensions = true, .customWidth = 163.f, .customHeight = 90.f
    });

    float animateTime = .6f;

    registry->emplace<DebugName>(muzzle, DebugName{"Muzzle"});
    registry->emplace<WorldPosition>(muzzle, WorldPosition {pos});
    registry->emplace<LocalPosition>(muzzle, LocalPosition{Vector2(0,0)});
    registry->emplace<Rotation>(muzzle, Rotation{angle});
    registry->emplace<LocalRotation>(muzzle, LocalRotation{0});

    auto opacityTween = Tween::Opacity(registry, muzzle, 1, 0, animateTime)
            .SetEase(Ease::Type::OutQuint)
            ->GetEntity();

    auto scaleTween = Tween::Scale(registry, muzzle, Vector2{1, 1}, Vector2{0, 0.3f}, animateTime)
            .SetEase(Ease::Type::OutQuint)
            ->GetEntity();

    registry->emplace<MuzzleFlash>(shooter, MuzzleFlash{ animateTime, animateTime, muzzle, opacityTween, scaleTween});


    EntityRelationSystem::Assign(registry, shooter, muzzle);
}
