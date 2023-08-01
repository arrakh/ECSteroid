//
// Created by Arya Rakha on 8/1/2023.
//

#include "SFMLTextureService.h"
#include <filesystem>

namespace fs = std::filesystem;

void SFMLTextureService::Load() {
    for (const auto& entry : fs::directory_iterator(OD_TEXTURES_PATH)) {
        if (!entry.is_regular_file()) continue;

        auto path = entry.path().string();

        sf::Texture texture;
        if (!texture.loadFromFile(path))
            throw std::invalid_argument("Trying to load Texture but could not load " + path);

        auto id = entry.path().stem().string();
        textureMap[id] = std::make_shared<sf::Texture>(texture);
    }
}

void SFMLTextureService::Unload() {

}

std::shared_ptr<sf::Texture> SFMLTextureService::Get(std::string path) {
    auto it = textureMap.find(path);
    if (it == textureMap.end()) throw std::invalid_argument("Could not find texture with name " + path);
    else return it->second;
}
