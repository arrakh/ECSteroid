//
// Created by Arya Rakha on 6/25/2023.
//

#ifndef ECSTEROID_BULLETLIFETIMESYSTEM_H
#define ECSTEROID_BULLETLIFETIMESYSTEM_H


#include "core/IUpdatableSystem.h"

class BulletLifetimeSystem : public IUpdatableSystem {
public:
    void Update(entt::registry *registry) override;

};


#endif //ECSTEROID_BULLETLIFETIMESYSTEM_H
