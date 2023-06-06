//
// Created by Arya Rakha on 6/5/2023.
//

#ifndef CMAKESFMLPROJECT_IEVENTREGISTRABLESYSTEM_H
#define CMAKESFMLPROJECT_IEVENTREGISTRABLESYSTEM_H


#include "entt/entity/registry.hpp"

class IEventRegistrableSystem {
public:
    virtual void RegisterEvents(entt::registry* registry) = 0;
    virtual void UnregisterEvents(entt::registry* registry) = 0;
};


#endif //CMAKESFMLPROJECT_IEVENTREGISTRABLESYSTEM_H
