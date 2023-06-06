//
// Created by Arya Rakha on 6/4/2023.
//

#include <iostream>
#include "LocalPlayerMovementSystem.h"
#include "../components/Position.h"
#include "../components/Speed.h"
#include "../util/Time.h"
#include "../components/LocalPlayer.h"
#include "../components/PhysicsBody.h"

void LocalPlayerMovementSystem::Update(entt::registry* registry) {
    float direction { 0.0f };
    float rotation { 0.0f };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) rotation = - 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) rotation = 1.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction = - 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction = 1.0f;

    if (direction == 0.0f) return;
    auto view = registry->view<PhysicsBody, Position, Speed, LocalPlayer>();
    for ( auto [entity, pb, position, speed] : view.each() ) {
        float magnitude = direction * speed.value * Time::deltaTime();

        b2Vec2 forceVector = b2Vec2(cos(pb.body->GetAngle()), sin(pb.body->GetAngle()));

        std::cout << "Applying Force: " << magnitude << " To Player\n";
        pb.body->ApplyForceToCenter(forceVector, true);
    }
}
