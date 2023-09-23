//
// Created by Arya Rakha on 9/23/2023.
//

#ifndef ECSTEROID_BUTTON_H
#define ECSTEROID_BUTTON_H


#include <functional>
#include <string>
#include <SFML/Graphics.hpp>

enum ButtonState { NORMAL, HIGHLIGHTED, PRESSED };

struct ButtonDefinition {
    const std::function<void()>& callback;
    sf::View* viewTarget;
    const sf::FloatRect rect;
};

struct Button {
    const std::function<void()>& callback;
    ButtonState lastState;
    ButtonState currentState;
    sf::View* viewTarget;
    sf::Sprite* sprite;
    const sf::FloatRect rect;
};

struct ButtonStateSpritesDefinition {
    std::string normalSpriteName;
    std::string highlightedSpriteName;
    std::string pressedSpriteName;
};

struct ButtonStateSprites{
    sf::Texture* normalTexture;
    sf::Texture* highlightedTexture;
    sf::Texture* pressedTexture;
};



#endif //ECSTEROID_BUTTON_H
