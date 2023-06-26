//
// Created by Arya Rakha on 6/26/2023.
//

#ifndef ECSTEROID_IFINALUPDATABLESYSTEM_H
#define ECSTEROID_IFINALUPDATABLESYSTEM_H

#include <entt/entt.hpp>

class IFinalUpdatableSystem {
public:
    virtual void FinalUpdate(entt::registry* registry) = 0;
};


#endif //ECSTEROID_IFINALUPDATABLESYSTEM_H
