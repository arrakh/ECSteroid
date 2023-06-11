//
// Created by Arya Rakha on 6/11/2023.
//

#include "SFMLSpriteSystem.h"
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

}
