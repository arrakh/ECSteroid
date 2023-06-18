//
// Created by rafizidny on 6/18/2023.
//

#ifndef ECSTEROID_SHOOTCOOLDOWNSYSTEM_H
#define ECSTEROID_SHOOTCOOLDOWNSYSTEM_H


#include "core/IUpdatableSystem.h"

class ShootCooldownSystem : public IUpdatableSystem {
public:
    void Update(entt::registry *registry) override;
};


#endif //ECSTEROID_SHOOTCOOLDOWNSYSTEM_H
