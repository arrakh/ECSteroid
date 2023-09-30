//
// Created by Arya Rakha on 9/23/2023.
//

#ifndef ECSTEROID_BUTTONOBJECT_H
#define ECSTEROID_BUTTONOBJECT_H


#include <functional>
#include <string>
#include <SFML/Graphics.hpp>
#include "../datatype/Vector2.h"

enum ButtonState { NORMAL, HIGHLIGHTED, PRESSED };

struct Button {
    Vector2 size;
    Vector2 pivot = {0.5f, 0.5f};
    std::function<void()> callback;
    bool active = true;
};

struct ButtonObject {
    sf::FloatRect rect;
    ButtonState state = NORMAL;
};

struct ButtonStateSpritesDefinition {
    std::string normalSpriteName;
    std::string highlightedSpriteName;
    std::string pressedSpriteName;
};

struct ButtonStateSprites{
    std::shared_ptr<sf::Texture> normalTexture;
    std::shared_ptr<sf::Texture> highlightedTexture;
    std::shared_ptr<sf::Texture> pressedTexture;
};



#endif //ECSTEROID_BUTTONOBJECT_H
