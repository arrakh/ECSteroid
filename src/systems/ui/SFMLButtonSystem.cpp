//
// Created by Arya Rakha on 9/23/2023.
//

#include <iostream>
#include "SFMLButtonSystem.h"
#include "../../components/SFMLViewTarget.h"
#include "../../components/debug/DebugName.h"
#include "../../components/WorldPosition.h"
#include "../../datatype/Vector2.h"

void SFMLButtonSystem::Update(entt::registry *registry) {
    GenerateButtons(registry);

    auto defaultView = sfWindow->windowPtr->getView();

    DetectButtonClick(registry, defaultView);

    bool isClicking = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    auto buttons = registry->view<ButtonObject, Button, WorldPosition>();
    for (auto [entity, buttonObject, button, position] : buttons.each()) {
        if (!button.active) continue;

        auto pos = position.vector;
        float left = pos.x - (button.size.x * button.pivot.x);
        float top = pos.y - (button.size.y * button.pivot.y);

        registry->patch<ButtonObject>(entity, [&left, &top, &button](ButtonObject& buttonObject){
            buttonObject.rect.left = left;
            buttonObject.rect.top = top;
            buttonObject.rect.width = button.size.x;
            buttonObject.rect.height = button.size.y;
        });

        if (!IsOverlappingButton(registry, entity, buttonObject, defaultView)) {
            registry->patch<ButtonObject>(entity, [&](ButtonObject& btn){ btn.state = NORMAL;});
            continue;
        }

        focusedButtonEntity = entity;
        auto newState = isClicking ? PRESSED : HIGHLIGHTED;
        registry->patch<ButtonObject>(entity, [&newState](ButtonObject& btn){ btn.state = newState;});
    }
}

bool SFMLButtonSystem::IsOverlappingButton(entt::registry *registry, entt::entity entity, ButtonObject& button, sf::View defaultView){
    auto viewTarget = registry->try_get<SFMLViewTarget>(entity);
    auto view = viewTarget != nullptr ? *viewTarget->targetView : defaultView;
    auto mousePos = sf::Mouse::getPosition(*sfWindow->windowPtr);
    auto viewPos = sfWindow->windowPtr->mapPixelToCoords(mousePos, view);

    return button.rect.contains(viewPos);
}

void SFMLButtonSystem::DetectButtonClick(entt::registry *registry, sf::View defaultView) {
    if (!registry->valid(focusedButtonEntity)) return;

    auto& buttonObject = registry->get<ButtonObject>(focusedButtonEntity);
    auto& button = registry->get<Button>(focusedButtonEntity);

    if (!button.active) return;

    if (buttonObject.state != PRESSED) return;

    bool isClicking = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    bool isOverlapping = IsOverlappingButton(registry, focusedButtonEntity, buttonObject, defaultView);

    if (isClicking || !isOverlapping) return;
    button.callback();
    focusedButtonEntity = entt::null;
}

void SFMLButtonSystem::GenerateButtons(entt::registry *registry) {
    auto definitions = registry->view<Button, WorldPosition>(entt::exclude<ButtonObject>);
    for (auto [entity, definition, position] : definitions.each()) {
        Vector2 pos = position.vector;

        float left = pos.x - (definition.size.x * definition.pivot.x);
        float top = pos.y - (definition.size.y * definition.pivot.y);
        sf::FloatRect rect{left, top, definition.size.x, definition.size.y};

        registry->emplace<ButtonObject>(entity, ButtonObject {rect, NORMAL});
    }
}
