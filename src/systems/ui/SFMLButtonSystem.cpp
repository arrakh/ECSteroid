//
// Created by Arya Rakha on 9/23/2023.
//

#include <iostream>
#include "SFMLButtonSystem.h"
#include "../../components/SFMLViewTarget.h"
#include "../../components/debug/DebugName.h"
#include "../../components/Position.h"
#include "../../datatype/Vector2.h"

void SFMLButtonSystem::Update(entt::registry *registry) {
    GenerateButtons(registry);

    auto defaultView = sfWindow->windowPtr->getView();

    DetectButtonClick(registry, defaultView);

    bool isClicking = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    auto buttons = registry->view<Button>();
    for (auto [entity, button] : buttons.each()) {
        if (!button.active) continue;


        if (!IsOverlappingButton(registry, entity, button, defaultView)) {
            registry->patch<Button>(entity, [&](Button& btn){btn.state = NORMAL;});
            continue;
        }

        focusedButtonEntity = entity;
        auto newState = isClicking ? PRESSED : HIGHLIGHTED;
        registry->patch<Button>(entity, [&newState](Button& btn){btn.state = newState;});
    }
}

bool SFMLButtonSystem::IsOverlappingButton(entt::registry *registry, entt::entity entity, Button& button, sf::View defaultView){
    auto viewTarget = registry->try_get<SFMLViewTarget>(entity);
    auto view = viewTarget != nullptr ? *viewTarget->targetView : defaultView;
    auto mousePos = sf::Mouse::getPosition(*sfWindow->windowPtr);
    auto viewPos = sfWindow->windowPtr->mapPixelToCoords(mousePos, view);

    return button.rect.contains(viewPos);
}

void SFMLButtonSystem::DetectButtonClick(entt::registry *registry, sf::View defaultView) {
    if (!registry->valid(focusedButtonEntity)) return;

    auto& button = registry->get<Button>(focusedButtonEntity);

    if (button.state != PRESSED) return;

    bool isClicking = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    bool isOverlapping = IsOverlappingButton(registry, focusedButtonEntity, button, defaultView);

    if (isClicking || !isOverlapping) return;
    button.callback();
    focusedButtonEntity = entt::null;
}

void SFMLButtonSystem::GenerateButtons(entt::registry *registry) {
    auto definitions = registry->view<ButtonDefinition>();
    for (auto [entity, definition] : definitions.each()) {
        auto posComp = registry->try_get<Position>(entity);
        Vector2 pos = posComp != nullptr ? posComp->vector : Vector2{0.f , 0.f};

        float left = pos.x - (definition.size.x * definition.pivot.x);
        float top = pos.y - (definition.size.y * definition.pivot.y);
        sf::FloatRect rect{left, top, definition.size.x, definition.size.y};

        registry->emplace<Button>(entity, Button {definition.callback, rect});
    }

    registry->clear<ButtonDefinition>();
}
