//
// Created by Arya Rakha on 6/4/2023.
//

#include <iostream>
#include "LocalPlayerMovementSystem.h"
#include "../util/Time.h"
#include "../components/LocalPlayer.h"
#include "../events/TestEvent.h"

void LocalPlayerMovementSystem::Update(entt::registry* registry) {
    float thrust {0.0f };
    float rotation { 0.0f };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) rotation = - 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) rotation = 1.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) thrust = - 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) thrust = 1.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
        TestEvent e {1, thrust};
        publisher->Publish(e);
    }

    if (thrust != 0.0f) {
        auto view = registry->view<PhysicsBody, MoveSpeed, LocalPlayer>();
        for ( auto [entity, pb, speed] : view.each() )
            UpdatePosition(entity, &pb, &speed, thrust);
    }

    auto view = registry->view<PhysicsBody, SpinSpeed, LocalPlayer>();
    for ( auto [entity, pb, speed] : view.each() )
        UpdateRotation(entity, &pb, &speed, rotation);
}

void
LocalPlayerMovementSystem::UpdatePosition(entt::entity entity, PhysicsBody *pb, MoveSpeed *speed, const float direction) {
    float magnitude = direction * speed->value * Time::deltaTime();

    float angleOffset = 90.f;
    auto angle = pb->body->GetAngle() + (angleOffset * b2_pi / 180.f);
    b2Vec2 forceVector = b2Vec2(cos(angle) * magnitude, sin(angle) * magnitude);

    //std::cout << "Applying Force x: " << forceVector.x << ", y: " << forceVector.y << " To Player\n";
    pb->body->ApplyForceToCenter(forceVector, true);
}

void
LocalPlayerMovementSystem::UpdateRotation(entt::entity entity, PhysicsBody *pb, SpinSpeed *speed, const float direction) {
    float angleChange = direction * speed->value * Time::deltaTime();
    float newAngle = pb->body->GetAngle() + angleChange;
    pb->body->SetAngularVelocity(0.f);
    pb->body->SetTransform(pb->body->GetPosition(), newAngle);

}
