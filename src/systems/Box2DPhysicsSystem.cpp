//
// Created by Arya Rakha on 6/6/2023.
//

#include <iostream>
#include "Box2DPhysicsSystem.h"
#include "../util/Time.h"
#include "../components/CircleShape.h"
#include "../components/Rotation.h"
#include "../components/Position.h"


void Box2DPhysicsSystem::Load(entt::registry *registry) {

}

void Box2DPhysicsSystem::Unload() {

}

void Box2DPhysicsSystem::FixedUpdate(entt::registry *registry) {
    world.Step(Time::fixedDeltaTime(), 6, 2);

    registry->view<PhysicsDefinition>().each([this, registry](auto entity, PhysicsDefinition def){
        CreateBody(registry, entity, def);
    });

    registry->clear<PhysicsDefinition>();

    registry->view<PhysicsBody>().each([this, registry](auto entity, PhysicsBody body){
        UpdateTransform(registry, entity, body);
    });
}

void Box2DPhysicsSystem::CreateBody(entt::registry *registry, entt::entity entity, PhysicsDefinition& def) {
    PhysicsBody comp;
    comp.body = world.CreateBody(&def.bodyDef);

    auto circleData = registry->try_get<CircleShape>(entity);
    if (circleData != nullptr){
        b2CircleShape* circle = new b2CircleShape();
        circle->m_radius = circleData->radius;
        comp.shape = circle;
    }

    // Create a fixture definition and attach the shape to it
    b2FixtureDef fixtureDef;
    fixtureDef.shape = comp.shape;
    fixtureDef.userData.pointer = static_cast<std::uintptr_t>(entity);

    comp.fixture = comp.body->CreateFixture(&fixtureDef);

    UpdateTransform(registry, entity, comp);

    std::cout << "CREATED PHYSICS BODY\n";
    registry->emplace<PhysicsBody>(entity, comp);
}

void Box2DPhysicsSystem::UpdateTransform(entt::registry *registry, entt::entity entity, PhysicsBody &comp) {
    if (registry->any_of<Position>(entity)){
        registry->patch<Position>(entity, [&comp](Position& pos) {
            auto ppos = comp.body->GetPosition();
            pos.vector = Vector2 { ppos};
            std::cout << "PHYSICS POSITION IS X: " << ppos.x << " Y: " << ppos.y << "\n";
        });

    }

    if (registry->any_of<Rotation>(entity)){
        registry->patch<Rotation>(entity, [&comp](Rotation& rot){
            rot.value = comp.body->GetAngle() * 180.0f / b2_pi;
        });
    }
}
