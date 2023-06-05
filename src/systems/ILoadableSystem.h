//
// Created by Arya Rakha on 6/4/2023.
//

#ifndef CMAKESFMLPROJECT_ILOADABLESYSTEM_H
#define CMAKESFMLPROJECT_ILOADABLESYSTEM_H


#include "entt/entity/registry.hpp"

class ILoadableSystem {
public:
    virtual void Load(entt::registry* registry) = 0;
    virtual void Unload() = 0;
};


#endif //CMAKESFMLPROJECT_ILOADABLESYSTEM_H
