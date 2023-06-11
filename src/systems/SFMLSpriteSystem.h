//
// Created by Arya Rakha on 6/11/2023.
//

#ifndef CMAKESFMLPROJECT_SFMLSPRITESYSTEM_H
#define CMAKESFMLPROJECT_SFMLSPRITESYSTEM_H


#include "core/ILoadableSystem.h"
#include "core/IUpdatableSystem.h"
#include <SFML/Graphics.hpp>

class SFMLSpriteSystem : public ILoadableSystem, public IUpdatableSystem  {
public:
    void Load(entt::registry *registry) override;

    void Unload() override;

    void Update(entt::registry *registry) override;

private:
    const std::string OD_TEXTURES_PATH = "assets/textures-on-demand";

    std::unordered_map<std::string, sf::Texture> textureMap;
};


#endif //CMAKESFMLPROJECT_SFMLSPRITESYSTEM_H
