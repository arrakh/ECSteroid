//
// Created by Arya Rakha on 6/26/2023.
//

#ifndef ECSTEROID_ILATEUPDATABLESYSTEM_H
#define ECSTEROID_ILATEUPDATABLESYSTEM_H


#include "entt/entity/registry.hpp"

class ILateUpdatableSystem {
public:
    virtual void LateUpdate(entt::registry* registry) = 0;
};


#endif //ECSTEROID_ILATEUPDATABLESYSTEM_H
