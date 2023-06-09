//
// Created by Arya Rakha on 6/4/2023.
//

#ifndef CMAKESFMLPROJECT_LOCALPLAYERMOVEMENTSYSTEM_H
#define CMAKESFMLPROJECT_LOCALPLAYERMOVEMENTSYSTEM_H

#include "core/IUpdatableSystem.h"
#include "../components/PhysicsBody.h"
#include "../components/Position.h"
#include "../components/Speed.h"
#include "../components/Rotation.h"
#include "core/IEventPublisherSystem.h"

class LocalPlayerMovementSystem : public IUpdatableSystem, public IEventPublisherSystem {
public:
    void Update(entt::registry* registry) override;

    void OnInjectPublisher(Events::Publisher *pub) override { this->publisher = pub; }

private:
    Events::Publisher* publisher;

    static void UpdatePosition(entt::entity entity, PhysicsBody* pb, MoveSpeed* speed, float direction);
    static void UpdateRotation(entt::entity entity, PhysicsBody* pb, SpinSpeed* speed, float direction);
};


#endif //CMAKESFMLPROJECT_LOCALPLAYERMOVEMENTSYSTEM_H
