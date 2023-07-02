//
// Created by Arya Rakha on 6/30/2023.
//

#ifndef ECSTEROID_ASTEROIDSPAWNERSYSTEM_H
#define ECSTEROID_ASTEROIDSPAWNERSYSTEM_H


#include "core/IEventSubscriberSystem.h"
#include "core/ILoadableSystem.h"
#include "../datatype/Vector2.h"
#include "../components/Asteroid.h"

class AsteroidSpawnerSystem : public IEventSubscriberSystem, public ILoadableSystem {
public:
    void SubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) override;

    void UnsubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) override;

    void Load(entt::registry *registry) override;

    void Unload() override;

private:
    static void CreateAsteroid(entt::registry *registry, Asteroid definition, Vector2 pos, Vector2 velocity);

    void OnAsteroidDestroyed(entt::registry &registry, entt::entity entity);
};


#endif //ECSTEROID_ASTEROIDSPAWNERSYSTEM_H
