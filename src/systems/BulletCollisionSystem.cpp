//
// Created by Arya Rakha on 6/25/2023.
//

#include <iostream>
#include "BulletCollisionSystem.h"
#include "../components/bullet/BulletDestroyOnCollision.h"
#include "../components/bullet/BulletDamage.h"
#include "../components/Health.h"
#include "../components/Killer.h"
#include "../components/bullet/BulletOwner.h"

void BulletCollisionSystem::SubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {
    subscriber->Subscribe<CollisionEvent>([this, registry](const CollisionEvent& event){ OnCollision(registry, event); });
}

void BulletCollisionSystem::UnsubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {
    subscriber->Unsubscribe<CollisionEvent>([this, registry](const CollisionEvent& event){ OnCollision(registry, event); });
}

void BulletCollisionSystem::OnCollision(entt::registry *registry, const CollisionEvent& event) {
    HandlePossibleBulletCollision(registry, event.a, event.b);
    HandlePossibleBulletCollision(registry, event.b, event.a);
}

void BulletCollisionSystem::HandlePossibleBulletCollision(entt::registry *registry, const entt::entity possibleBullet, const entt::entity other) {

    auto damageData = registry->try_get<BulletDamage>(possibleBullet);
    auto otherHealthData = registry->try_get<Health>(other);

    if (damageData == nullptr || otherHealthData == nullptr) return;

    auto newHealth = otherHealthData->health - damageData->damage;

    auto bulletOwner = registry->try_get<BulletOwner>(possibleBullet);

    if (bulletOwner != nullptr && newHealth <= 0.f) registry->emplace_or_replace<Killer>(other, Killer { bulletOwner->entity });
    registry->patch<Health>(other, [newHealth](Health& data){data.health = newHealth;});

    bool destroyOnColl = registry->all_of<BulletDestroyOnCollision>(possibleBullet);
    if (destroyOnColl) registry->destroy(possibleBullet);
}
