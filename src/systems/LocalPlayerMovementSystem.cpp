//
// Created by Arya Rakha on 6/4/2023.
//

#include <iostream>
#include "LocalPlayerMovementSystem.h"
#include "../components/Position.h"
#include "../components/Speed.h"
#include "../util/Time.h"

void LocalPlayerMovementSystem::Update(entt::registry* registry) {
    Vector2 desiredPosition { 0.0f, 0.0f };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) desiredPosition.x = - 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) desiredPosition.x = 1.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) desiredPosition.y = - 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) desiredPosition.y = 1.0f;

    auto view = registry->view<Position, Speed>();
    for ( auto [entity, position, speed] : view.each() ) {
        auto finalPos = desiredPosition * (speed.value * Time::deltaTime());
        auto newPos = position.vector + finalPos;

        registry->patch<Position>(entity, [newPos](auto& pos){
           pos.vector = newPos;
        });

        std::cout << "\nPlayer Position TICK " << Time::deltaTime() << " - x:" << newPos.x << " y:" << newPos.y;
    }
}
