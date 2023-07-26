//
// Created by Arya Rakha on 6/6/2023.
//

#include <iostream>
#include "Box2DPhysicsSystem.h"
#include "../util/Time.h"
#include "../components/Rotation.h"
#include "../components/Position.h"
#include "../events/CollisionEvent.h"


void Box2DPhysicsSystem::Load(entt::registry *registry) {
    world.SetContactListener(this);
}

void Box2DPhysicsSystem::Unload() {

}

void Box2DPhysicsSystem::FixedUpdate(entt::registry *registry) {
    for (auto& body : destroyQueue) {
        world.DestroyBody(body);
    }

    destroyQueue.clear();

    world.Step(Time::fixedDeltaTime(), 6, 2);
    world.ClearForces();

    registry->view<PhysicsDefinition>().each([this, registry](auto entity, PhysicsDefinition def){
        CreateBody(registry, entity, def);
    });

    registry->clear<PhysicsDefinition>();

    registry->view<PhysicsBody>().each([this, registry](auto entity, PhysicsBody body){
        if (!registry->valid(entity)) return;
        UpdateTransform(registry, entity, body);
    });
}

void Box2DPhysicsSystem::CreateBody(entt::registry *registry, entt::entity entity, PhysicsDefinition& def) {
    PhysicsBody comp;

    comp.body = world.CreateBody(&def.bodyDef);
    comp.fixture = comp.body->CreateFixture(&def.fixtureDef);

    UpdateTransform(registry, entity, comp);

    registry->emplace<PhysicsBody>(entity, comp);
}

void Box2DPhysicsSystem::UpdateTransform(entt::registry *registry, entt::entity entity, PhysicsBody &comp) {

    //comp.body->ApplyForceToCenter(, true);

    if (registry->any_of<Position>(entity)){
        registry->patch<Position>(entity, [&comp](Position& pos) {
            auto ppos = comp.body->GetPosition();
            pos.vector = Vector2 { ppos};
            //std::cout << "PHYSICS POSITION IS X: " << ppos.x << " Y: " << ppos.y << "\n";
        });

    }

    if (registry->any_of<Rotation>(entity)){
        registry->patch<Rotation>(entity, [&comp](Rotation& rot){
            rot.value = comp.body->GetAngle() * 180.0f / b2_pi;
        });
    }
}

void Box2DPhysicsSystem::BeginContact(b2Contact *contact) {
    auto fixtureA = contact->GetFixtureA();
    auto fixtureB = contact->GetFixtureB();

    auto entityA = static_cast<entt::entity>(fixtureA->GetUserData().pointer);
    auto entityB = static_cast<entt::entity>(fixtureB->GetUserData().pointer);

    CollisionEvent event{entityA, entityB};
    eventPublisher->Publish(event);
}

void Box2DPhysicsSystem::SubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {
    registry->on_destroy<PhysicsBody>().connect<&Box2DPhysicsSystem::OnBodyDestroyed>(this);
}

void Box2DPhysicsSystem::UnsubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {
}

void Box2DPhysicsSystem::OnBodyDestroyed(entt::registry &registry, entt::entity entity) {
    auto bodyData = registry.try_get<PhysicsBody>(entity);
    if (bodyData == nullptr) throw std::invalid_argument("TRYING TO DESTROY BODY WITHOUT PHYSICS BODY???");

    if (registry.valid(entity)) destroyQueue.push_back(bodyData->body);
}
