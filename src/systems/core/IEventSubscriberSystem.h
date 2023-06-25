//
// Created by Arya Rakha on 6/5/2023.
//

#ifndef CMAKESFMLPROJECT_IEVENTREGISTRABLESYSTEM_H
#define CMAKESFMLPROJECT_IEVENTREGISTRABLESYSTEM_H


#include "entt/entity/registry.hpp"
#include "EventSystem.h"

class IEventSubscriberSystem {
public:
    virtual void SubscribeEvents(entt::registry* registry, Events::Subscriber* subscriber) = 0;
    virtual void UnsubscribeEvents(entt::registry* registry, Events::Subscriber* subscriber) = 0;
};


#endif //CMAKESFMLPROJECT_IEVENTREGISTRABLESYSTEM_H
