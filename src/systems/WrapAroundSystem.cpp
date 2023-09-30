//
// Created by Arya Rakha on 6/12/2023.
//

#include <iostream>
#include "../components/WorldPosition.h"
#include "WrapAroundSystem.h"
#include "../application/Application.h"
#include "../components/WrapAround.h"
#include "../components/PhysicsBody.h"

void WrapAroundSystem::Update(entt::registry *registry) {
    auto& window = *sfWindow->windowPtr;

    Vector2 bottomRight {window.mapPixelToCoords(sf::Vector2i{window.getSize()})};
    Vector2 topLeft {window.mapPixelToCoords(sf::Vector2i{0, 0})};

    auto view = registry->view<WorldPosition, WrapAround>(entt::exclude<PhysicsBody>);
    for (auto [entity, pos] : view.each()) {
        auto newPos = GetWrappedPosition(pos.vector, topLeft, bottomRight);

        registry->patch<WorldPosition>(entity, [&newPos](WorldPosition& pos){ pos.vector = newPos;});
    }
}

void WrapAroundSystem::FixedUpdate(entt::registry *registry) {
    auto& window = *sfWindow->windowPtr;

    Vector2 bottomRight {window.mapPixelToCoords(sf::Vector2i{window.getSize()})};
    Vector2 topLeft {window.mapPixelToCoords(sf::Vector2i{0, 0})};

    auto view = registry->view<WorldPosition, PhysicsBody, WrapAround>();
    for (auto [entity, pos, physicsData] : view.each()) {
        if (!physicsData.body->IsEnabled()) continue;

        auto newPos = GetWrappedPosition(pos.vector, topLeft, bottomRight);

        physicsData.body->SetTransform(newPos, physicsData.body->GetAngle());

        registry->patch<WorldPosition>(entity, [&newPos](WorldPosition& pos){ pos.vector = newPos;});
    }
}


Vector2 WrapAroundSystem::GetWrappedPosition(const Vector2 pos, const Vector2 topLeft, const Vector2 bottomRight) {
    Vector2 newPos { pos };

    if (pos.x > bottomRight.x) newPos.x = topLeft.x;
    else if (pos.x < topLeft.x) newPos.x = bottomRight.x;

    if (pos.y < topLeft.y) newPos.y = bottomRight.y;
    else if (pos.y > bottomRight.y) newPos.y = topLeft.y;

    return newPos;
}