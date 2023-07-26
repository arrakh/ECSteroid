//
// Created by Arya Rakha on 7/25/2023.
//

#include "AsteroidScoreSystem.h"
#include "../events/EntityDeathEvent.h"
#include "../components/Asteroid.h"
#include "../components/Killer.h"
#include "../components/Score.h"

const float speedScoreFactor = 1.f;
const float sizeScoreFactor = 1.f;
const float speedLowestValue = 60.f;
const float sizeHighestValue = 110.f;
const float scoreMultiplier = 100.f;

void AsteroidScoreSystem::SubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {
    subscriber->Subscribe<EntityDeathEvent>([this, registry](const EntityDeathEvent &event)
    { OnPossibleAsteroidDestroyed(registry, event.entity); });
}

void AsteroidScoreSystem::UnsubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {
    subscriber->Unsubscribe<EntityDeathEvent>([this, registry](const EntityDeathEvent &event)
    { OnPossibleAsteroidDestroyed(registry, event.entity); });
}

void AsteroidScoreSystem::OnPossibleAsteroidDestroyed(entt::registry *registry, entt::entity possibleAsteroid) {
    auto asteroidData = registry->try_get<Asteroid>(possibleAsteroid);
    if (asteroidData == nullptr) return;

    auto killerData = registry->try_get<Killer>(possibleAsteroid);
    if (killerData == nullptr) return;

    float speedScore = asteroidData->speed / speedLowestValue * speedScoreFactor;
    float sizeScore = sizeHighestValue / asteroidData->size * sizeScoreFactor;
    float score = (speedScore + sizeScore) * scoreMultiplier;

    auto scoreData = registry->try_get<Score>(killerData->entity);
    if (scoreData != nullptr) score += scoreData->value;

    registry->emplace_or_replace<Score>(killerData->entity, Score {static_cast <int> (std::floor(score))});
}
