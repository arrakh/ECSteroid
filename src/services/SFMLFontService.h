//
// Created by Arya Rakha on 8/1/2023.
//

#ifndef ECSTEROID_SFMLFONTSERVICE_H
#define ECSTEROID_SFMLFONTSERVICE_H


#include <string>
#include <unordered_map>
#include <memory>
#include "SFML/Graphics.hpp"
#include "core/ILocatableService.h"
#include "core/ILoadableService.h"

class SFMLFontService : public ILocatableService, public ILoadableService{
public:
    void Load() override;

    void Unload() override;

    std::shared_ptr<sf::Font> Get(std::string path);

private:
    const std::string FONTS_PATH = "assets/fonts";

    std::unordered_map<std::string, std::shared_ptr<sf::Font>> fontMap;
};


#endif //ECSTEROID_SFMLFONTSERVICE_H
