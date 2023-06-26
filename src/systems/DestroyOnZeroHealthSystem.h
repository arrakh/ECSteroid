//
// Created by Arya Rakha on 6/26/2023.
//

#ifndef ECSTEROID_DESTROYONZEROHEALTHSYSTEM_H
#define ECSTEROID_DESTROYONZEROHEALTHSYSTEM_H


#include "core/ILateUpdatableSystem.h"
#include "core/IEventSubscriberSystem.h"

class DestroyOnZeroHealthSystem : public ILateUpdatableSystem, public IEventSubscriberSystem {
public:
    void SubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) override;

    void UnsubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) override;

    void LateUpdate(entt::registry *registry) override;

private:
    void OnHealthUpdated(entt::registry &registry, entt::entity entity);
};


#endif //ECSTEROID_DESTROYONZEROHEALTHSYSTEM_H
