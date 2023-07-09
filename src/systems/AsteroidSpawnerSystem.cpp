//
// Created by Arya Rakha on 6/30/2023.
//

#include <iostream>
#include "AsteroidSpawnerSystem.h"
#include "../components/debug/Box2DDebug.h"
#include "../components/Sprite.h"
#include "../components/Health.h"
#include "../components/WrapAround.h"
#include "../components/Rotation.h"
#include "../components/Position.h"
#include "../components/PhysicsDefinition.h"
#include "../util/Random.h"
#include "../Application.h"
#include "../events/EntityDeathEvent.h"
#include "../datatype/CollisionGroup.h"

void AsteroidSpawnerSystem::SubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {
    subscriber->Subscribe<EntityDeathEvent>([this, registry](const EntityDeathEvent &event)
    {
        OnAsteroidDestroyed(*registry, event.entity);
    });
}

void AsteroidSpawnerSystem::UnsubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {

}

void AsteroidSpawnerSystem::OnAsteroidDestroyed(entt::registry &registry, entt::entity entity) {
    auto asteroidData = registry.try_get<Asteroid>(entity);

    if (asteroidData == nullptr) return;

    auto position = registry.try_get<Position>(entity);

    if (position == nullptr) return;

    if (asteroidData->splitCount <= 0) return;

    int randCount = Random::Range(2, 3);

    float newSize = asteroidData->size / 2.f;
    float newSpeed = asteroidData->speed * 1.5f;
    float newRotSpeed = asteroidData->rotationSpeed * 1.5f;
    float newHealth = asteroidData->startHealth * 0.8f;

    for (int i = 0; i < randCount; ++i) {
        Vector2 randDir = Random::UnitCircle();

        float randAngle = Random::Range(0.f, 360.f);

        Vector2 newPos = position->vector + randDir * newSize;

        Asteroid def {.size = newSize, .speed = newSpeed, .rotationSpeed = newRotSpeed,
                .startRotation = randAngle, .startHealth = newHealth,
                .splitCount = asteroidData->splitCount - 1};

        CreateAsteroid(&registry, def, newPos, randDir);
    }
}

void AsteroidSpawnerSystem::CreateAsteroid(entt::registry *registry, const Asteroid definition, const Vector2 pos, const Vector2 direction) {
    auto asteroid = registry->create();

    registry->emplace<SpriteDefinition>(asteroid, SpriteDefinition {
            .spriteName =  "meteorBrown_big4", .initialOrder =  0,
            .useCustomDimensions = true, .customWidth = definition.size, .customHeight = definition.size
    });

    registry->emplace<Box2DDebugDefinition>(asteroid, Box2DDebugDefinition { sf::Color::Green, 1.f});

    registry->emplace<Health>(asteroid, Health{definition.startHealth});
    registry->emplace<Asteroid>(asteroid, definition);

    registry->emplace<WrapAround>(asteroid, WrapAround {});
    registry->emplace<Position>(asteroid, Position {pos});
    registry->emplace<Rotation>(asteroid, Rotation {definition.startRotation});

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 0.0f;
    bodyDef.position = pos;
    bodyDef.angle = definition.startRotation * b2_pi / 180.0f;

    bodyDef.linearVelocity = direction * definition.speed;
    bodyDef.angularVelocity = definition.rotationSpeed * 0.01f;

    auto shape = new b2CircleShape;
    shape->m_radius = definition.size * 0.01f / 2.f;

    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.2f;
    fixtureDef.friction = 0.1f;
    fixtureDef.shape = shape;
    fixtureDef.filter.categoryBits = CATEGORY_ENEMY;
    fixtureDef.userData.pointer = static_cast<std::uintptr_t>(asteroid);

    registry->emplace<PhysicsDefinition>(asteroid, PhysicsDefinition {bodyDef, fixtureDef, shape});
}

void AsteroidSpawnerSystem::Load(entt::registry *registry) {
    for (int i = 0; i < 10; ++i) {
        int randSplitCount = Random::Range(1, 2);

        float randHealth = Random::Range(55.f, 70.f);

        float randSize = Random::Range(70.f, 110.f);
        float doubleSize = randSize * 2;

        float hw = Application::Width / 2.f;
        float hh = Application::Height / 2.f;

        float x = Random::Range(-hw + doubleSize ,hw - doubleSize);
        float y = Random::Range(-hh + doubleSize ,hh - doubleSize);
        float randDamage = Random::Range(70.f, 90.f);
        float randAngle = Random::Range(0.f, 360.f);
        float randSpeed = Random::Range(60.f, 130.f);
        float randRotSpeed = Random::Range(50.f, 300.f);
        Vector2 randDir = Random::UnitCircle();

        Asteroid def {.size = randSize, .speed = randSpeed, .rotationSpeed = randRotSpeed, .startRotation = randAngle,
                      .startHealth = randHealth, .damageOnHit = randDamage, .splitCount = randSplitCount};

        CreateAsteroid(registry, def, Vector2{x, y},  randDir);
    }
}

void AsteroidSpawnerSystem::Unload() {

}

