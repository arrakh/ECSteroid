//
// Created by Arya Rakha on 6/26/2023.
//

#ifndef ECSTEROID_DESTROYONZEROHEALTHSYSTEM_H
#define ECSTEROID_DESTROYONZEROHEALTHSYSTEM_H


#include "core/ILateUpdatableSystem.h"
#include "core/IEventSubscriberSystem.h"
#include "core/IEventPublisherSystem.h"

class DestroyOnZeroHealthSystem : public ILateUpdatableSystem, public IEventSubscriberSystem, public IEventPublisherSystem {
public:
    void OnInjectPublisher(Events::Publisher *pub) override { publisher = pub; }

    void SubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) override;

    void UnsubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) override;

    void LateUpdate(entt::registry *registry) override;

private:
    void OnHealthUpdated(entt::registry &registry, entt::entity entity);
    Events::Publisher *publisher;
};


#endif //ECSTEROID_DESTROYONZEROHEALTHSYSTEM_H
