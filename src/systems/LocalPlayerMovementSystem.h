//
// Created by Arya Rakha on 6/4/2023.
//

#ifndef CMAKESFMLPROJECT_LOCALPLAYERMOVEMENTSYSTEM_H
#define CMAKESFMLPROJECT_LOCALPLAYERMOVEMENTSYSTEM_H

#include "IUpdatableSystem.h"

class LocalPlayerMovementSystem : public IUpdatableSystem {
public:
    void Update(entt::registry* registry) override;
};


#endif //CMAKESFMLPROJECT_LOCALPLAYERMOVEMENTSYSTEM_H
