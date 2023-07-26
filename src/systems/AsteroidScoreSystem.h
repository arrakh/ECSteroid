//
// Created by Arya Rakha on 7/25/2023.
//

#ifndef ECSTEROID_ASTEROIDSCORESYSTEM_H
#define ECSTEROID_ASTEROIDSCORESYSTEM_H


#include "core/IEventSubscriberSystem.h"

class AsteroidScoreSystem : public IEventSubscriberSystem {
    void SubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) override;

    void UnsubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) override;

private:
    void OnPossibleAsteroidDestroyed(entt::registry* registry, entt::entity asteroid);
};


#endif //ECSTEROID_ASTEROIDSCORESYSTEM_H
