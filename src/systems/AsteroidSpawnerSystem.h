//
// Created by Arya Rakha on 6/30/2023.
//

#ifndef ECSTEROID_ASTEROIDSPAWNERSYSTEM_H
#define ECSTEROID_ASTEROIDSPAWNERSYSTEM_H


#include "core/IEventSubscriberSystem.h"
#include "core/ILoadableSystem.h"
#include "../datatype/Vector2.h"
#include "../components/Asteroid.h"
#include "../datatype/CreateAsteroidParameter.h"

class AsteroidSpawnerSystem : public IEventSubscriberSystem {
public:
    void SubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) override;

    void UnsubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) override;

private:
    static void CreateAsteroid(entt::registry *registry, CreateAsteroidParameter param);

    void OnAsteroidDestroyed(entt::registry &registry, entt::entity entity);
};


#endif //ECSTEROID_ASTEROIDSPAWNERSYSTEM_H
