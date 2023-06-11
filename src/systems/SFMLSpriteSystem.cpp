//
// Created by Arya Rakha on 6/11/2023.
//

#include "SFMLSpriteSystem.h"
#include "../components/Sprite.h"
#include "../components/SFMLTransformable.h"
#include "../components/SFMLDrawable.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

void SFMLSpriteSystem::Load(entt::registry *registry) {
    for (const auto& entry : fs::directory_iterator(OD_TEXTURES_PATH)) {
        if (!entry.is_regular_file()) continue;

        auto path = entry.path().string();

        sf::Texture texture;
        if (!texture.loadFromFile(path))
            throw std::invalid_argument("Trying to load Texture but could not load " + path);

        auto id = entry.path().stem().string();
        textureMap[id] = texture;
    }

}

void SFMLSpriteSystem::Unload() {

}

void SFMLSpriteSystem::Update(entt::registry *registry) {
    auto view = registry->view<SpriteDefinition>();
    for (auto [entity, def] : view.each()) {
        auto transformable = registry->try_get<SFMLTransformable>(entity);
        if (transformable != nullptr) throw std::invalid_argument("Trying to create sprite but entity already has Transformable!");

        auto drawable = registry->try_get<SFMLDrawable>(entity);
        if (drawable != nullptr) throw std::invalid_argument("Trying to create sprite but entity already has Drawable!");

        auto it = textureMap.find(def.spriteName);
        if (it == textureMap.end()) throw std::invalid_argument("Could not find texture with name " + def.spriteName);

        sf::Sprite sprite {it->second};

        if (def.center){
            auto size = it->second.getSize();
            sprite.setOrigin(size.x/2.f, size.y/2.f);
        }

        sprite.setRotation(def.initialAngle);
        sprite.setScale(def.initialScale, def.initialScale);

        auto spritePtr = std::make_shared<sf::Sprite>(sprite);

        registry->emplace<SFMLTransformable>(entity, SFMLTransformable { spritePtr });
        registry->emplace<SFMLDrawable>(entity, SFMLDrawable { 0, spritePtr });
    }

    registry->clear<SpriteDefinition>();
}


