//
// Created by Arya Rakha on 6/4/2023.
//

#include "RectangleDrawSystem.h"
#include "../components/Position.h"
#include "../components/SFMLCircleShape.h"

void RectangleDrawSystem::Render(entt::registry* registry, sf::RenderTarget* renderTarget) {
    auto view = registry->view<SFMLCircleShape, Position>();

    for (auto [entity, shape, pos] : view.each()) {
        shape.shape.setPosition(pos.vector.x, pos.vector.y);
        renderTarget->draw(shape.shape);
    }
}

int RectangleDrawSystem::GetRenderOrder() {
    return 0;
}
