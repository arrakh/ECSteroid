//
// Created by Arya Rakha on 9/24/2023.
//

#ifndef ECSTEROID_SFMLSPRITE_H
#define ECSTEROID_SFMLSPRITE_H

#include <memory>
#include "SFML/Graphics.hpp"
#include "../datatype/Vector2.h"

struct SFMLSprite{
    std::shared_ptr<sf::Sprite> sprite;
    Vector2 spriteScale;
};

#endif //ECSTEROID_SFMLSPRITE_H
