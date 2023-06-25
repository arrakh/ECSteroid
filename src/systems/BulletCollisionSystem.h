//
// Created by Arya Rakha on 6/25/2023.
//

#ifndef ECSTEROID_BULLETCOLLISIONSYSTEM_H
#define ECSTEROID_BULLETCOLLISIONSYSTEM_H


#include "core/IEventSubscriberSystem.h"
#include "../events/CollisionEvent.h"

class BulletCollisionSystem : public IEventSubscriberSystem {
public:
    void SubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) override;

    void UnsubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) override;

private:
    void OnCollision(entt::registry *registry, const CollisionEvent& event);

    void HandlePossibleBulletCollision(entt::registry *registry, entt::entity possibleBullet);
};


#endif //ECSTEROID_BULLETCOLLISIONSYSTEM_H
