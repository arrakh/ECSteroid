//
// Created by Arya Rakha on 6/11/2023.
//

#include "SFMLSpriteSystem.h"
#include "../components/Sprite.h"
#include "../components/SFMLTransformable.h"
#include "../components/SFMLDrawable.h"
#include "../components/SFMLSprite.h"
#include <iostream>

void SFMLSpriteSystem::LocateServices(std::shared_ptr<ServiceLocator> serviceLocator) {
    textureService = serviceLocator->Locate<SFMLTextureService>();
}

void SFMLSpriteSystem::Update(entt::registry *registry) {
    auto view = registry->view<SpriteDefinition>();
    for (auto [entity, def] : view.each()) {
        auto transformable = registry->try_get<SFMLTransformable>(entity);
        if (transformable != nullptr) throw std::invalid_argument("Trying to create sprite but entity already has Transformable!");

        auto drawable = registry->try_get<SFMLDrawable>(entity);
        if (drawable != nullptr) throw std::invalid_argument("Trying to create sprite but entity already has Drawable!");

        auto texture = textureService->Get(def.spriteName);
        sf::Sprite sprite {*texture};

        auto size = texture->getSize();

        if (def.tiled){
            float width = def.useCustomDimensions ? def.customWidth : size.x;
            float height = def.useCustomDimensions ? def.customHeight : size.y;
            int x = std::floor(width);
            int y = std::floor(height);
            sprite.setTextureRect(sf::IntRect {0, 0, x, y});
            sprite.setOrigin(width * def.pivot.x, height * def.pivot.y);

            texture->setRepeated(true);
        } else {
            sprite.setOrigin(size.x * def.pivot.x, size.y * def.pivot.y);

            if (def.useCustomDimensions){
                float scaleX = def.customWidth / size.x;
                float scaleY = def.customHeight / size.y;

                sprite.setScale(scaleX, scaleY);
            }
        }

        auto spritePtr = std::make_shared<sf::Sprite>(sprite);

        registry->emplace<SFMLSprite>(entity, SFMLSprite { spritePtr });
        registry->emplace<SFMLTransformable>(entity, SFMLTransformable { spritePtr });
        registry->emplace<SFMLDrawable>(entity, SFMLDrawable { def.initialOrder, spritePtr });
    }

    registry->clear<SpriteDefinition>();
}



