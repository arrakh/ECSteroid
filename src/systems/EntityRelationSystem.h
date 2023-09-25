//
// Created by Arya Rakha on 9/24/2023.
//

#ifndef ECSTEROID_ENTITYRELATIONSYSTEM_H
#define ECSTEROID_ENTITYRELATIONSYSTEM_H


#include "core/IUpdatableSystem.h"

class EntityRelationSystem : public IUpdatableSystem {
public:
    void Update(entt::registry *registry) override;

    static void Assign(entt::registry *registry, entt::entity parent, entt::entity child);
};


#endif //ECSTEROID_ENTITYRELATIONSYSTEM_H
