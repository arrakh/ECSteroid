//
// Created by Arya Rakha on 10/8/2023.
//

#ifndef ECSTEROID_IEARLYUPDATABLESYSTEM_H
#define ECSTEROID_IEARLYUPDATABLESYSTEM_H

#include <entt/entt.hpp>

class IEarlyUpdatableSystem {
public:
    virtual void EarlyUpdate(entt::registry* registry) = 0;
};

#endif //ECSTEROID_IEARLYUPDATABLESYSTEM_H
