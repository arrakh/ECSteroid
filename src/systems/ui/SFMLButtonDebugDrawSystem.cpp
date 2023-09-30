//
// Created by Arya Rakha on 9/24/2023.
//

#include "SFMLButtonDebugDrawSystem.h"
#include "../../components/ButtonObject.h"
#include "../../components/SFMLViewTarget.h"
#include "../../components/debug/SFMLButtonDebug.h"
#include "../../datatype/Vector2.h"

void SFMLButtonDebugDrawSystem::Render(entt::registry *registry) {
    auto buttons = registry->view<ButtonObject>();

    auto defaultView = sfWindow->windowPtr->getView();

    for (auto [entity, button] : buttons.each()) {
        auto debugComp = registry->try_get<SFMLButtonDebug>(entity);
        if (debugComp == nullptr){
            registry->emplace<SFMLButtonDebug>(entity, SFMLButtonDebug {std::make_unique<sf::RectangleShape>(button.rect.getSize())});
            debugComp = &registry->get<SFMLButtonDebug>(entity);
            debugComp->shape->setFillColor(sf::Color::Transparent);
            debugComp->shape->setOutlineColor(sf::Color::Red);
            debugComp->shape->setOutlineThickness(2.f);
        }

        auto viewTarget = registry->try_get<SFMLViewTarget>(entity);
        auto view = viewTarget != nullptr ? *viewTarget->targetView : defaultView;

        sfWindow->windowPtr->setView(view);

        debugComp->shape->setPosition(button.rect.getPosition());

        sfWindow->windowPtr->draw(*debugComp->shape);
    }
}

int SFMLButtonDebugDrawSystem::GetRenderOrder() {
    return 10000;
}
