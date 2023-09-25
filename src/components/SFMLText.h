//
// Created by Arya Rakha on 9/24/2023.
//

#ifndef ECSTEROID_SFMLTEXT_H
#define ECSTEROID_SFMLTEXT_H

#include <string>
#include "SFML/Graphics.hpp"

struct SFMLText {
    std::string text;
    int size;
    sf::Color color;
    std::string fontName;
    int drawOrder;
};

struct SFMLTextObject {
    std::shared_ptr<sf::Text> sfText;
};

#endif //ECSTEROID_SFMLTEXT_H
