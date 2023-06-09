//
// Created by Arya Rakha on 6/6/2023.
//

#include <iostream>
#include "Box2DPhysicsSystem.h"
#include "../util/Time.h"
#include "../components/Rotation.h"
#include "../components/Position.h"


void Box2DPhysicsSystem::Load(entt::registry *registry) {
    std::cout << "WORLD GRAVITY IS " << world.GetGravity().y << "\n";
}

void Box2DPhysicsSystem::Unload() {

}

void Box2DPhysicsSystem::FixedUpdate(entt::registry *registry) {
    world.Step(Time::fixedDeltaTime(), 6, 2);
    world.ClearForces();

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

    std::cout << "Will create body def with type " << def.bodyDef.type << std::endl;
    comp.body = world.CreateBody(&def.bodyDef);
    comp.fixture = comp.body->CreateFixture(&def.fixtureDef);

    UpdateTransform(registry, entity, comp);

    std::cout << "CREATED PHYSICS BODY \n";
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
