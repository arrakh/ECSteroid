//
// Created by Arya Rakha on 7/9/2023.
//

#ifndef ECSTEROID_ASTEROIDTOPLAYERCOLLISIONSYSTEM_H
#define ECSTEROID_ASTEROIDTOPLAYERCOLLISIONSYSTEM_H


#include "core/IEventSubscriberSystem.h"
#include "../events/CollisionEvent.h"

class AsteroidToPlayerCollisionSystem : public IEventSubscriberSystem {
public:
    void SubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) override;

    void UnsubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) override;

private:
    void OnCollision(entt::registry *registry, const CollisionEvent& event);

    void HandlePossibleAsteroidCollision(entt::registry *registry, entt::entity possibleAsteroid, const entt::entity possiblePlayer);
};


#endif //ECSTEROID_ASTEROIDTOPLAYERCOLLISIONSYSTEM_H
