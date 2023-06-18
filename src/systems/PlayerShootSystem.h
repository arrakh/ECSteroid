//
// Created by rafizidny on 6/18/2023.
//

#ifndef ECSTEROID_PLAYERSHOOTSYSTEM_H
#define ECSTEROID_PLAYERSHOOTSYSTEM_H


#include "core/IUpdatableSystem.h"

class PlayerShootSystem: public IUpdatableSystem {
public:
    void Update(entt::registry *registry) override;
};


#endif //ECSTEROID_PLAYERSHOOTSYSTEM_H
