//
// Created by Arya Rakha on 9/24/2023.
//

#include <iostream>
#include "SFMLButtonStatesSpriteSystem.h"
#include "../../components/Button.h"
#include "../../components/SFMLSprite.h"

void SFMLButtonStatesSpriteSystem::LateUpdate(entt::registry *registry) {
    auto definitions = registry->view<ButtonStateSpritesDefinition>();
    for (auto [entity, definition] : definitions.each()) {
        auto normal = textureService->Get(definition.normalSpriteName);
        auto highlighted = textureService->Get(definition.highlightedSpriteName);
        auto pressed = textureService->Get(definition.pressedSpriteName);
        registry->emplace<ButtonStateSprites>(entity, ButtonStateSprites{normal, highlighted, pressed});
    }

    registry->clear<ButtonStateSpritesDefinition>();

    auto buttons = registry->view<Button, ButtonStateSprites, SFMLSprite>();
    for (auto [entity, button, sprites, spriteRef] : buttons.each()) {
        auto color = button.active ? sf::Color::White : sf::Color{255, 255, 255, 77};
        spriteRef.sprite->setColor(color);
        if (!button.active){
            spriteRef.sprite->setTexture(*sprites.normalTexture);
            continue;
        }

        switch (button.state) {
            case HIGHLIGHTED: spriteRef.sprite->setTexture(*sprites.highlightedTexture); break;
            case PRESSED: spriteRef.sprite->setTexture(*sprites.pressedTexture); break;
            default: spriteRef.sprite->setTexture(*sprites.normalTexture); break;
        }
    }
}

void SFMLButtonStatesSpriteSystem::LocateServices(std::shared_ptr<ServiceLocator> serviceLocator) {
    textureService = serviceLocator->Locate<SFMLTextureService>();
}
