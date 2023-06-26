//
// Created by rafizidny on 6/18/2023.
//

#include "PlayerShootSystem.h"
#include "../components/LocalPlayer.h"
#include "../util/Time.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../components/Rotation.h"
#include "../components/Position.h"
#include "../components/Sprite.h"
#include "../components/PhysicsDefinition.h"
#include "../components/debug/Box2DDebug.h"
#include "../components/bullet/BulletLifetime.h"
#include "../components/bullet/BulletDestroyOnCollision.h"
#include "../components/bullet/BulletDamage.h"
#include "../components/PhysicsBody.h"

void PlayerShootSystem::Update(entt::registry *registry) {

    auto cooldown = registry->view<ShootAbilityCooldown>();
    for (auto [entity, cooldownData] : cooldown.each()) {
        cooldownData.value -= Time::deltaTime();
        if (cooldownData.value <= 0.f) registry->remove<ShootAbilityCooldown>(entity);
    }

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) return;

    auto shoot = registry->view<ShootAbility, LocalPlayer, Position, Rotation>(entt::exclude<ShootAbilityCooldown>);
    for (auto [entity, shootData, pos, rot] : shoot.each()) {
        if (shootData.cooldown > 0.f) registry->emplace<ShootAbilityCooldown>(entity, ShootAbilityCooldown { shootData.cooldown });

        CreateBullet(entity, registry, pos.vector, rot.value, shootData);
    }
}

void PlayerShootSystem::Load(entt::registry *registry) {
    registry->sort<ShootAbility, ShootAbilityCooldown>();
}

void PlayerShootSystem::Unload() {

}

void PlayerShootSystem::CreateBullet(entt::entity shooter, entt::registry *registry, const Vector2 pos, const float angle, ShootAbility data) {
    auto bullet = registry->create();
    float size = 5.f;
    float halfSize = size / 2.f;

    registry->emplace<Box2DDebugDefinition>(bullet, Box2DDebugDefinition { sf::Color::Green, 1.f});
    registry->emplace<SpriteDefinition>(bullet, SpriteDefinition {
            .spriteName =  "meteorGrey_tiny1", .initialOrder =  0,
            .useCustomDimensions = true, .customWidth = size, .customHeight = size
    });

    float rad = angle * M_PI / 180;
    Vector2 shootDir {cos(rad) , sin(rad)};
    Vector2 bulletPos =  pos + (shootDir * data.startDistance);

    /*auto bodyData = registry->try_get<PhysicsBody>(shooter);
    if (bodyData != nullptr){
        bulletPos = bulletPos + Vector2{bodyData->body->GetLinearVelocity()};
    }*/

    registry->emplace<Position>(bullet, Position {bulletPos});
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
    bodyDef.linearVelocity = shootDir * data.bulletSpeed;

    auto shape = new b2CircleShape;
    shape->m_radius = size * 0.01f / 2.f;

    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.0001f;
    fixtureDef.friction = 0.f;
    fixtureDef.shape = shape;
    fixtureDef.userData.pointer = static_cast<std::uintptr_t>(bullet);

    registry->emplace<PhysicsDefinition>(bullet, PhysicsDefinition {bodyDef, fixtureDef, shape});
}
