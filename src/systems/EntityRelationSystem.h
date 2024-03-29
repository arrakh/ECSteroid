//
// Created by Arya Rakha on 9/24/2023.
//

#ifndef ECSTEROID_ENTITYRELATIONSYSTEM_H
#define ECSTEROID_ENTITYRELATIONSYSTEM_H


#include "core/IUpdatableSystem.h"
#include "core/IEventSubscriberSystem.h"
#include "core/IEarlyUpdatableSystem.h"

class EntityRelationSystem : public IEarlyUpdatableSystem, public IUpdatableSystem {
public:
    void Update(entt::registry *registry) override;

    static void Assign(entt::registry *registry, entt::entity parent, entt::entity child);

    void EarlyUpdate(entt::registry *registry) override;

private:
    void UpdateEntityAndChildren(entt::registry& registry, entt::entity entity);
};


#endif //ECSTEROID_ENTITYRELATIONSYSTEM_H
