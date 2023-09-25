//
// Created by Arya Rakha on 9/23/2023.
//

#ifndef ECSTEROID_BUTTON_H
#define ECSTEROID_BUTTON_H


#include <functional>
#include <string>
#include <SFML/Graphics.hpp>
#include "../datatype/Vector2.h"

enum ButtonState { NORMAL, HIGHLIGHTED, PRESSED };

struct ButtonDefinition {
    Vector2 size;
    Vector2 pivot = {0.5f, 0.5f};

    std::function<void()> callback;
};

struct Button {
    std::function<void()> callback;
    const sf::FloatRect rect;
    bool active = true;
    ButtonState state;
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



#endif //ECSTEROID_BUTTON_H
