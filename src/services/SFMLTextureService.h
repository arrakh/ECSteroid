//
// Created by Arya Rakha on 8/1/2023.
//

#ifndef ECSTEROID_SFMLTEXTURESERVICE_H
#define ECSTEROID_SFMLTEXTURESERVICE_H


#include "core/ILocatableService.h"
#include "core/ILoadableService.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>

class SFMLTextureService : public ILocatableService, public ILoadableService {
public:
    void Load() override;

    void Unload() override;

    std::shared_ptr<sf::Texture> Get(std::string path);

private:
    const std::string OD_TEXTURES_PATH = "assets/textures-on-demand";

    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textureMap;
};


#endif //ECSTEROID_SFMLTEXTURESERVICE_H
