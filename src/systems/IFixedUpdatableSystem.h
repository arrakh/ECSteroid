//
// Created by Arya Rakha on 6/4/2023.
//

#ifndef CMAKESFMLPROJECT_IFIXEDUPDATABLESYSTEM_H
#define CMAKESFMLPROJECT_IFIXEDUPDATABLESYSTEM_H


#include "entt/entity/registry.hpp"

class IFixedUpdatableSystem {
public:
    virtual void FixedUpdate(entt::registry* registry) = 0;
};


#endif //CMAKESFMLPROJECT_IFIXEDUPDATABLESYSTEM_H
