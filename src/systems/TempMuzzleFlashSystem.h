//
// Created by Arya Rakha on 10/8/2023.
//

#ifndef ECSTEROID_TEMPMUZZLEFLASHSYSTEM_H
#define ECSTEROID_TEMPMUZZLEFLASHSYSTEM_H


#include "core/IUpdatableSystem.h"
#include "core/IEventSubscriberSystem.h"

class TempMuzzleFlashSystem : public IUpdatableSystem, public IEventSubscriberSystem {
public:
    void SubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) override;

    void UnsubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) override;

    void Update(entt::registry *registry) override;

};


#endif //ECSTEROID_TEMPMUZZLEFLASHSYSTEM_H
