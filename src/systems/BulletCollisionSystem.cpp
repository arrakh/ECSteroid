//
// Created by Arya Rakha on 6/25/2023.
//

#include <iostream>
#include "BulletCollisionSystem.h"
#include "../components/bullet/BulletDestroyOnCollision.h"

void BulletCollisionSystem::SubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {
    subscriber->Subscribe<CollisionEvent>([this, registry](const CollisionEvent& event){ OnCollision(registry, event); });
}

void BulletCollisionSystem::UnsubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {
    subscriber->Unsubscribe<CollisionEvent>([this, registry](const CollisionEvent& event){ OnCollision(registry, event); });
}

void BulletCollisionSystem::OnCollision(entt::registry *registry, const CollisionEvent& event) {
    HandlePossibleBulletCollision(registry, event.a);
    HandlePossibleBulletCollision(registry, event.b);
}

void BulletCollisionSystem::HandlePossibleBulletCollision(entt::registry *registry, const entt::entity possibleBullet) {
    auto destroyOnColl = registry->all_of<BulletDestroyOnCollision>(possibleBullet);
    if (destroyOnColl) registry->destroy(possibleBullet);
}
