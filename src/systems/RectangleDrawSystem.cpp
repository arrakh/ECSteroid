//
// Created by Arya Rakha on 6/4/2023.
//

#include "RectangleDrawSystem.h"
#include "../components/Position.h"
#include "../components/SFMLRectangleShape.h"

void RectangleDrawSystem::Render(entt::registry* registry, sf::RenderTarget* renderTarget) {
    auto view = registry->view<SFMLRectangleShape, Position>();

    for (auto [entity, shape, pos] : view.each()) {
        shape.shape.setPosition(pos.vector.x, pos.vector.y);
        renderTarget->draw(shape.shape);
    }
}
