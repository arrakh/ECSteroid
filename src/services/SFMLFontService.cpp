//
// Created by Arya Rakha on 8/1/2023.
//

#include "SFMLFontService.h"
#include <filesystem>

namespace fs = std::filesystem;

void SFMLFontService::Load() {
    for (const auto& entry : fs::directory_iterator(FONTS_PATH)) {
        if (!entry.is_regular_file()) continue;

        auto path = entry.path().string();

        sf::Font font;
        if (!font.loadFromFile(path))
            throw std::invalid_argument("Trying to load Font but could not load " + path);

        auto id = entry.path().stem().string();
        fontMap[id] = std::make_shared<sf::Font>(font);
    }
}

void SFMLFontService::Unload() {

}

std::shared_ptr<sf::Font> SFMLFontService::Get(std::string path) {
    auto it = fontMap.find(path);
    if (it == fontMap.end()) throw std::invalid_argument("Could not find font with name " + path);
    else return it->second;
}
