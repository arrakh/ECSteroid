//
// Created by Arya Rakha on 6/4/2023.
//

#ifndef CMAKESFMLPROJECT_IUPDATABLESYSTEM_H
#define CMAKESFMLPROJECT_IUPDATABLESYSTEM_H

#include "entt/entt.hpp"

class IUpdatableSystem {
public:
    virtual void Update(entt::registry* registry) = 0;
};


#endif //CMAKESFMLPROJECT_IUPDATABLESYSTEM_H
