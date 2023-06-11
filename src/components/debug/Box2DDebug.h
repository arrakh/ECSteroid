//
// Created by Arya Rakha on 6/11/2023.
//

#ifndef CMAKESFMLPROJECT_BOX2DDEBUG_H
#define CMAKESFMLPROJECT_BOX2DDEBUG_H

#include <SFML/Graphics.hpp>

struct Box2DDebugDefinition {
    const sf::Color outlineColor;
    const float outlineSize;
};

struct Box2DDebugData {
    std::shared_ptr<sf::Shape> shape;
    const sf::Color outlineColor;
    const float outlineSize;
};


#endif //CMAKESFMLPROJECT_BOX2DDEBUG_H
