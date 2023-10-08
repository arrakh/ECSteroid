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
#include "../components/WorldPosition.h"
#include "../components/PhysicsDefinition.h"
#include "../util/Random.h"
#include "../application/Application.h"
#include "../events/EntityDeathEvent.h"
#include "../datatype/CollisionGroup.h"
#include "../events/StartWaveEvent.h"

void AsteroidSpawnerSystem::SubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {
    subscriber->Subscribe<EntityDeathEvent>([this, registry](const EntityDeathEvent &event)
    {
        OnAsteroidDestroyed(*registry, event.entity);
    });

    subscriber->Subscribe<StartWaveEvent>([this, registry](const StartWaveEvent &event){
        std::cout << "STARTING WAVE EVENT\n";
        for (auto& param : event.params) { CreateAsteroid(registry, param); }
    });
}

void AsteroidSpawnerSystem::UnsubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {

}

void AsteroidSpawnerSystem::OnAsteroidDestroyed(entt::registry &registry, entt::entity entity) {
    auto asteroidData = registry.try_get<Asteroid>(entity);

    if (asteroidData == nullptr) return;

    auto position = registry.try_get<WorldPosition>(entity);

    if (position == nullptr) return;

    if (asteroidData->splitCount <= 0) return;

    int randCount = Random::Range(2, 3);

    float newSize = asteroidData->size / 2.f;
    float newSpeed = asteroidData->speed * 1.5f;
    float newRotSpeed = asteroidData->rotationSpeed * 1.5f;
    float newHealth = asteroidData->startHealth * 0.5f;
    float newDamage = asteroidData->damageOnHit * 1.3f;

    for (int i = 0; i < randCount; ++i) {
        Vector2 randDir = Random::UnitCircle();

        float randAngle = Random::Range(0.f, 360.f);

        Vector2 newPos = position->vector + randDir * newSize;

        Asteroid def {.size = newSize, .speed = newSpeed, .rotationSpeed = newRotSpeed,
                .startRotation = randAngle, .startHealth = newHealth, .damageOnHit = newDamage,
                .splitCount = asteroidData->splitCount - 1};

        CreateAsteroid(&registry, CreateAsteroidParameter{def, newPos, randDir});
    }
}

struct AsteroidSprite {
    std::string name;
    float minimumSize;
    float spriteSizeMultiplier;
};

AsteroidSprite definitions[5] = {
        AsteroidSprite {"asteroid-tiny-1", 0, 2.8f },
        AsteroidSprite {"asteroid-small-1", 25, 2.f },
        AsteroidSprite {"asteroid-medium-2", 33, 1.75f },
        AsteroidSprite {"asteroid-medium-1", 50, 1.5f },
        AsteroidSprite {"asteroid-large-1", 100, 1.5f },
};

AsteroidSprite GetSpriteDefinition(float size){
    AsteroidSprite def = definitions[0];

    for (int i = 1; i < 5; ++i) {
        //std::cout << "Checking if " << size << " is smaller than " << definitions[i].minimumSize << "\n";
        if (definitions[i].minimumSize > size) return def;
        def = definitions[i];
    }

    return def;
}

void AsteroidSpawnerSystem::CreateAsteroid(entt::registry *registry, const CreateAsteroidParameter param) {
    auto asteroid = registry->create();
    auto size = param.definition.size;
    auto spriteDef = GetSpriteDefinition(size);
    auto spriteSize = size * spriteDef.spriteSizeMultiplier;

    //std::cout << "Spawning asteroid size " << size << " with sprite " << spriteDef.name << "\n";

    registry->emplace<SpriteDefinition>(asteroid, SpriteDefinition {
            .spriteName =  spriteDef.name, .initialOrder =  0,
            .useCustomDimensions = true, .customWidth = spriteSize , .customHeight = spriteSize
    });

    registry->emplace<Box2DDebugDefinition>(asteroid, Box2DDebugDefinition { sf::Color::Green, 1.f});

    registry->emplace<Health>(asteroid, Health{param.definition.startHealth});
    registry->emplace<Asteroid>(asteroid, param.definition);

    registry->emplace<WrapAround>(asteroid, WrapAround {});
    registry->emplace<WorldPosition>(asteroid, WorldPosition {param.position});
    registry->emplace<Rotation>(asteroid, Rotation {param.definition.startRotation});

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 0.0f;
    bodyDef.position = param.position;
    bodyDef.angle = param.definition.startRotation * b2_pi / 180.0f;

    bodyDef.linearVelocity = param.direction * param.definition.speed;
    bodyDef.angularVelocity = param.definition.rotationSpeed * 0.01f;

    auto shape = new b2CircleShape;
    shape->m_radius = param.definition.size * 0.01f / 2.f;

    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.2f;
    fixtureDef.friction = 0.1f;
    fixtureDef.shape = shape;
    fixtureDef.filter.categoryBits = CATEGORY_ENEMY;
    fixtureDef.userData.pointer = static_cast<std::uintptr_t>(asteroid);

    registry->emplace<PhysicsDefinition>(asteroid, PhysicsDefinition {bodyDef, fixtureDef, shape});
}

void AsteroidSpawnerSystem::Load(entt::registry *registry) {
    int len = std::size(definitions);
    std::sort(definitions, definitions + len, [](AsteroidSprite &s1, AsteroidSprite &s2) { return s1.minimumSize < s2.minimumSize; });
}

void AsteroidSpawnerSystem::Unload() {

}

