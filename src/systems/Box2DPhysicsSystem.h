//
// Created by Arya Rakha on 6/6/2023.
//

#ifndef CMAKESFMLPROJECT_BOX2DPHYSICSSYSTEM_H
#define CMAKESFMLPROJECT_BOX2DPHYSICSSYSTEM_H


#include "core/IFixedUpdatableSystem.h"
#include "core/ILoadableSystem.h"
#include "../components/PhysicsDefinition.h"
#include "../components/PhysicsBody.h"
#include "core/IEventPublisherSystem.h"
#include <box2d/box2d.h>

class Box2DPhysicsSystem : public IFixedUpdatableSystem, public ILoadableSystem, public IEventPublisherSystem, public b2ContactListener {
public:
    void FixedUpdate(entt::registry *registry) override;

    void BeginContact(b2Contact* contact) override;

    void Load(entt::registry *registry) override;

    void Unload() override;

    void OnInjectPublisher(Events::Publisher *publisher) override { eventPublisher = publisher;}
private:
    b2World world { b2Vec2{0.f, 0.f} };
    Events::Publisher* eventPublisher;

    void CreateBody(entt::registry *registry, entt::entity entity, PhysicsDefinition& def);
    void UpdateTransform(entt::registry *registry, entt::entity entity, PhysicsBody& body);
};


#endif //CMAKESFMLPROJECT_BOX2DPHYSICSSYSTEM_H
