//
// Created by Arya Rakha on 9/24/2023.
//

#ifndef ECSTEROID_SFMLSPRITE_H
#define ECSTEROID_SFMLSPRITE_H

#include <memory>
#include "SFML/Graphics.hpp"

struct SFMLSprite{
    std::shared_ptr<sf::Sprite> sprite;
};

#endif //ECSTEROID_SFMLSPRITE_H
