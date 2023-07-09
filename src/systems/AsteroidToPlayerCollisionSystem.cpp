//
// Created by Arya Rakha on 7/9/2023.
//

#include <iostream>
#include "AsteroidToPlayerCollisionSystem.h"
#include "../components/Position.h"
#include "../components/Health.h"
#include "../components/Asteroid.h"
#include "../components/LocalPlayer.h"
#include "../components/PhysicsBody.h"

void AsteroidToPlayerCollisionSystem::SubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {
    subscriber->Subscribe<CollisionEvent>([this, registry](const CollisionEvent& event){ OnCollision(registry, event); });
}

void AsteroidToPlayerCollisionSystem::UnsubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {
    subscriber->Unsubscribe<CollisionEvent>([this, registry](const CollisionEvent& event){ OnCollision(registry, event); });
}

void AsteroidToPlayerCollisionSystem::OnCollision(entt::registry *registry, const CollisionEvent &event) {
    HandlePossibleAsteroidCollision(registry, event.a, event.b);
    HandlePossibleAsteroidCollision(registry, event.b, event.a);
}

void AsteroidToPlayerCollisionSystem::HandlePossibleAsteroidCollision(entt::registry *registry,
                                                                      entt::entity possibleAsteroid,
                                                                      const entt::entity possiblePlayer) {
    auto asteroid = registry->try_get<Asteroid>(possibleAsteroid);
    if (asteroid == nullptr) return;

    bool isPlayer = registry->all_of<LocalPlayer>(possiblePlayer);
    if (!isPlayer) return;

    auto health = registry->get<Health>(possiblePlayer);
    float newPlayerHealth = health.health - asteroid->damageOnHit;
    registry->patch<Health>(possiblePlayer, [newPlayerHealth](Health& data){data.health = newPlayerHealth;});

    auto asteroidBody = registry->get<PhysicsBody>(possibleAsteroid);
    auto playerBody = registry->get<PhysicsBody>(possiblePlayer);

    Vector2 playerPushDir{ playerBody.body->GetPosition() - asteroidBody.body->GetPosition() };
    Vector2 asteroidPushDir{ asteroidBody.body->GetPosition() - playerBody.body->GetPosition() };

    std::cout << "WILL PUSH PLAYER BY X:" << playerPushDir.x << " Y:" << playerPushDir.y;

    playerBody.body->ApplyLinearImpulseToCenter(playerPushDir * 0.2f, true);
    asteroidBody.body->ApplyLinearImpulseToCenter(asteroidPushDir * 0.2f, true);
}
