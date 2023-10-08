//
// Created by Arya Rakha on 10/8/2023.
//

#include "MainMenuUIBackgroundSystem.h"
#include "../../components/Sprite.h"
#include "../../components/WorldPosition.h"
#include "../../components/SFMLSprite.h"
#include "../../util/Time.h"

entt::entity bgEntity;
const float scrollRate = 20.f;

void MainMenuUIBackgroundSystem::OnLoad(entt::registry *registry) {
    uiView.reset(sf::FloatRect{0, 0, sfWindow->width, sfWindow->height});
    uiView.setViewport(GetViewport());
    uiView.setCenter(0, 0);

    bgEntity = registry->create();

    registry->emplace<WorldPosition>(bgEntity, WorldPosition {Vector2(0, 0)});
    registry->emplace<SpriteDefinition>(bgEntity, SpriteDefinition {
            .spriteName =  "darkPurple", .initialOrder =  -10000,
            .useCustomDimensions = true, .customWidth = 999999, .customHeight = 999999,
            .tiled = true
    });
}

void MainMenuUIBackgroundSystem::OnUnload() {

}


void MainMenuUIBackgroundSystem::Update(entt::registry *registry) {
    auto spriteObject = registry->try_get<SFMLSprite>(bgEntity);
    if (spriteObject == nullptr) return;

    auto origin = spriteObject->sprite->getOrigin();
    spriteObject->sprite->setOrigin(origin.x + (scrollRate * Time::deltaTime()), origin.y);
}

sf::FloatRect MainMenuUIBackgroundSystem::GetViewport() {
    return sf::FloatRect {0, 0, 1, 1};
}
